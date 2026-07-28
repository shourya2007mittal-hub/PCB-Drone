#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_BMP280.h>
#include <NimBLEDevice.h>

// --- PIN DEFINITIONS ---
#define PIN_M1 5
#define PIN_M2 17
#define PIN_M3 36
#define PIN_M4 37
#define PIN_LED 14

#define SDA_IMU 12
#define SCL_IMU 17 // Shared pin in schematic, note hardware conflict if both I2C buses run separately!
#define SDA_BARO 11
#define SCL_BARO 10

// PWM Setup
#define PWM_FREQ 20000 // 20kHz for brushed DC motor noise reduction
#define PWM_RES 8      // 0-255 duty cycle

// Bluetooth BLE UUIDs
#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

// Hardware Sensors
TwoWire I2C_IMU = TwoWire(0);
TwoWire I2C_BARO = TwoWire(1);
Adafruit_MPU6050 mpu;
Adafruit_BMP280 bmp(&I2C_BARO);

// Control Input Variables (from BLE)
volatile float req_throttle = 0; // 0 to 255
volatile float req_roll = 0;     // -30 to +30 deg
volatile float req_pitch = 0;    // -30 to +30 deg
volatile float req_yaw = 0;      // deg/s
volatile bool armed = false;

// Sensor Data
float roll_angle = 0, pitch_angle = 0;
float gyro_x = 0, gyro_y = 0, gyro_z = 0;
unsigned long last_time = 0;

// PID Gains
float kp_roll = 1.3, ki_roll = 0.01, kd_roll = 0.5;
float kp_pitch = 1.3, ki_pitch = 0.01, kd_pitch = 0.5;

// PID Variables
float error_roll, prev_error_roll, integral_roll;
float error_pitch, prev_error_pitch, integral_pitch;

// BLE Callbacks
class ServerCallbacks: public NimBLEServerCallbacks {
    void onConnect(NimBLEServer* pServer) {
        digitalWrite(PIN_LED, HIGH);
    }
    void onDisconnect(NimBLEServer* pServer) {
        digitalWrite(PIN_LED, LOW);
        armed = false; // Emergency stop on disconnect
    }
};

class CommandCallbacks: public NimBLECharacteristicCallbacks {
    void onWrite(NimBLECharacteristic *pCharacteristic) {
        std::string rxValue = pCharacteristic->getValue();
        if (rxValue.length() >= 5) {
            uint8_t cmd = rxValue[0];
            armed = (cmd == 1);
            req_throttle = (uint8_t)rxValue[1];
            req_roll = (int8_t)rxValue[2];     // Sent as offset -128 to 127
            req_pitch = (int8_t)rxValue[3];
            req_yaw = (int8_t)rxValue[4];
        }
    }
};

void setup() {
    Serial.begin(115200);
    pinMode(PIN_LED, OUTPUT);

    // PWM Setup for Motors
    ledcAttach(PIN_M1, PWM_FREQ, PWM_RES);
    ledcAttach(PIN_M2, PWM_FREQ, PWM_RES);
    ledcAttach(PIN_M3, PWM_FREQ, PWM_RES);
    ledcAttach(PIN_M4, PWM_FREQ, PWM_RES);

    // Stop Motors
    stopMotors();

    // Init I2C
    I2C_IMU.begin(SDA_IMU, SCL_IMU, 400000);
    I2C_BARO.begin(SDA_BARO, SCL_BARO, 100000);

    // Init MPU6050
    if (!mpu.begin(0x68, &I2C_IMU)) {
        Serial.println("Failed to find MPU6050 chip");
    }

    // Init BMP280
    if (!bmp.begin(0x76)) {
        Serial.println("Failed to find BMP280 chip");
    }

    // Bluetooth setup
    NimBLEDevice::init("PCB_Drone_ESP32");
    NimBLEServer *pServer = NimBLEDevice::createServer();
    pServer->setCallbacks(new ServerCallbacks());
    
    NimBLEService *pService = pServer->createService(SERVICE_UUID);
    NimBLECharacteristic *pCharacteristic = pService->createCharacteristic(
        CHARACTERISTIC_UUID,
        NIMBLE_PROPERTY::WRITE | NIMBLE_PROPERTY::WRITE_NR
    );
    pCharacteristic->setCallbacks(new CommandCallbacks());
    pService->start();

    NimBLEAdvertising *pAdvertising = NimBLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(SERVICE_UUID);
    pAdvertising->start();

    last_time = micros();
}

void loop() {
    // 1. Time delta
    unsigned long current_time = micros();
    float dt = (current_time - last_time) / 1000000.0;
    last_time = current_time;

    // 2. Read Sensors
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    // Calculate Accelerometer Angles
    float accel_roll = atan2(a.acceleration.y, a.acceleration.z) * 57.2958;
    float accel_pitch = atan2(-a.acceleration.x, sqrt(a.acceleration.y * a.acceleration.y + a.acceleration.z * a.acceleration.z)) * 57.2958;

    // Complementary Filter
    roll_angle = 0.96 * (roll_angle + g.gyro.x * dt * 57.2958) + 0.04 * accel_roll;
    pitch_angle = 0.96 * (pitch_angle + g.gyro.y * dt * 57.2958) + 0.04 * accel_pitch;

    // 3. PID Calculations
    if (armed && req_throttle > 15) {
        // Roll PID
        error_roll = req_roll - roll_angle;
        integral_roll += error_roll * dt;
        float derivative_roll = (error_roll - prev_error_roll) / dt;
        float out_roll = (kp_roll * error_roll) + (ki_roll * integral_roll) + (kd_roll * derivative_roll);
        prev_error_roll = error_roll;

        // Pitch PID
        error_pitch = req_pitch - pitch_angle;
        integral_pitch += error_pitch * dt;
        float derivative_pitch = (error_pitch - prev_error_pitch) / dt;
        float out_pitch = (kp_pitch * error_pitch) + (ki_pitch * integral_pitch) + (kd_pitch * derivative_pitch);
        prev_error_pitch = error_pitch;

        // Mixer
        int m1 = req_throttle + out_pitch + out_roll; // Front Left
        int m4 = req_throttle + out_pitch - out_roll; // Front Right
        int m2 = req_throttle - out_pitch + out_roll; // Rear Left
        int m3 = req_throttle - out_pitch - out_roll; // Rear Right

        // Drive Motors
        ledcWrite(PIN_M1, constrain(m1, 0, 255));
        ledcWrite(PIN_M2, constrain(m2, 0, 255));
        ledcWrite(PIN_M3, constrain(m3, 0, 255));
        ledcWrite(PIN_M4, constrain(m4, 0, 255));
    } else {
        stopMotors();
        resetPID();
    }

    delay(4); // ~250 Hz loop
}

void stopMotors() {
    ledcWrite(PIN_M1, 0);
    ledcWrite(PIN_M2, 0);
    ledcWrite(PIN_M3, 0);
    ledcWrite(PIN_M4, 0);
}

void resetPID() {
    integral_roll = 0; prev_error_roll = 0;
    integral_pitch = 0; prev_error_pitch = 0;
}