# PCB-Drone

<img width="767" height="660" alt="Screenshot 2026-08-05 230349" src="https://github.com/user-attachments/assets/51690f64-342c-4d99-8fe5-dd251fc04e64" />

So I made a custom PCB based on Esp32 . It holds an IMU and a Barometer for control . It has a normal 4 Motor Layout 2 motors will move  clock wise and 2 will be  anti-clock wise direction. Same direction motor will be diagonally apposite to each other. It have  used a 3.7V battery for power and a boot converter so that I can provide 5V to the Motors as we are using  ESP32 so we could controle it by our phone through bluetooth  .I have also design a web based controller , So that you could connect and controle the Bionic-Bird through your phone.

## Features

- Base on ESP32 Module
- Has IMU (MPU_6050)
- Has a Barometer (BMP280)
- Uses 4 8520 Motors 


## Components BOM





### 1. JLCPCB Manufacturing & Assembly Services
| Charge Description | Details / Notes | Cost ($) |
| :--- | :--- | :---: |
| **Components Cost** | 26 Matched Part Lines | $64.35 |
| **Setup Fee** | SMT Line Assembly Setup | $25.56 |
| **Stencil Fee** | SMT Laser Stencil | $8.21 |
| **Feeders Loading Fee** | Component Feeder Setup | $33.66 |
| **SMT Assembly** | Automated SMT Placement | $1.23 |
| **Hand-Soldering Labor Fee** | Through-hole / Manual Soldering | $3.58 |
| **Manual Assembly** | Specialized Component Insertion | $0.46 |
| **X-Ray Inspection** | BGA / QFN Joint Verification | $3.28 |
| **Packaging Fee** | Protective ESD Packaging | $0.50 |
| **Engineering Fee** | DFM / CAM File Verification | $4.00 |
| **Via Covering** | Tent / Plugged Vias | $0.00 |
| **PCB Fabrication Board Fee** | Raw Printed Circuit Board Cost | $9.90 |
| **PCB Shipping** | Express Courier to Destination | $11.53 |

---

### 2. External Hardware & Accessories
| Item | Description / Details | Qty | Link | Cost ($) |
| :--- | :--- | :---: | :---: | :---: |
| **8520 Coreless Motor** | Magnetic Micro Coreless Motor Set (2x CW, 2x CCW) | 1 Set | [Robu.in Link](https://robu.in/product/8520-magnetic-micro-coreless-motor-for-micro-quadcopters-2xcw-2xccw/) | $4.93 |
| **3.7V Battery** | KP Original 802540 1200mAh Single-Cell LiPo Battery | 1 Pcs | [Zbotic Link](https://zbotic.in/product/kp-original-802540-1200mah-3-7vsingle-cell-rechargeable-lipo-battery/) | $3.46 |

---

## 🧩 Complete Component Bill of Materials (BOM)

| Designator | Description / Value | Footprint | Qty | Price ($) | Part Details / Link |
| :--- | :--- | :--- | :---: | :---: | :--- |
| **C2** | 47uF 450V Electrolytic | 0201 | 2 | $1.333 | [KM476M450K25RR0VH2FP0](https://jlcpcb.com/partdetail/3127-KM476M450K25RR0VH2FP0/C2746) |
| **C3, C11, C18, C19** | 10uF 6.3V X5R | 0201 | 40 | $1.172 | [CL10A106MQ8NNNC](https://jlcpcb.com/partdetail/2043-CL10A106MQ8NNNC/C1691) |
| **C4, C13, C14** | 100nF 10V X5R | 0201 | 40 | $0.292 | [GRM033R61A104KE15D](https://jlcpcb.com/partdetail/MurataElectronics-GRM033R61A104KE15D/C76934) |
| **C5, C6** | 22uF 10V X5R | 0201 | 16 | $5.0256 | [1206X226K100NT](https://jlcpcb.com/partdetail/2211-1206X226K100NT/C1859) |
| **C9, C10, C12** | 0.1uF 10V X5R | 0201 | 40 | $0.236 | [0201X104K100NT](https://jlcpcb.com/partdetail/270391-0201X104K100NT/C284966) |
| **C7, C8, C15, C16** | 50nF Capacitors | 0201 | 8 | $6.532 | [LHC503SA2K0042NWB](https://jlcpcb.com/partdetail/launchip-LHC503SA2K0042NWB/C49233446) |
| **C1X1 - C6X1** | 1uF / 100nF Caps | 0805 | 22 | $0.3982 | [GZ2012D220TF](https://jlcpcb.com/partdetail/Sunlord-GZ2012D220TF/C1009) |
| **D1, D3** | LED Indicator | 0201 | 8 | $0.5448 | [XL0201SURC](https://jlcpcb.com/partdetail/XINGLIGHT-XL0201SURC/C3646923) |
| **D2** | Diode | 0201 | 2 | $0.3944 | [HIR204C](https://jlcpcb.com/partdetail/EverlightElec-HIR204C/C5118) |
| **D4, D5, D6, D7** | Schottky Diode | 0201 | 20 | $0.038 | [0201WMJ010JTEE](https://jlcpcb.com/partdetail/25797-0201WMJ010JTEE/C25054) |
| **F1** | Polyfuse | 0201 | 20 | $0.038 | [0201WMJ010JTEE](https://jlcpcb.com/partdetail/25797-0201WMJ010JTEE/C25054) |
| **D8** | 1N4001 Diode | DO-41 | 4 | $0.0776 | [1N4001](https://jlcpcb.com/partdetail/49200031-1N4001/C47018536) |
| **L1** | 2.2uH Power Inductor | 0201 | 20 | $0.750 | [CY43_22UH](https://jlcpcb.com/partdetail/SHOUHAN-CY43_22UH/C2929416) |
| **L2** | 4.7uH Inductor | 0603 | 20 | $0.414 | [SDFL1608Q4R7KTF](https://jlcpcb.com/partdetail/Sunlord-SDFL1608Q4R7KTF/C1034) |
| **Q1** | AO3401A P-Ch MOSFET | SOT-23 | 6 | $0.5688 | [AO3401A](https://jlcpcb.com/partdetail/Alpha_OmegaSemicon-AO3401A/C15127) |
| **Q2, Q3, Q4, Q5** | AO3400A N-Ch MOSFET | SOT-23 | 12 | $1.008 | [AO3400A](https://jlcpcb.com/partdetail/Alpha_OmegaSemicon-AO3400A/C20917) |
| **R1, R2** | 33 Ohm Resistor | 0201 | 20 | $0.062 | [0201WMJ0330TEE](https://jlcpcb.com/partdetail/416306-0201WMJ0330TEE/C423356) |
| **R3, R4** | 50K Resistor | 0201 | 6 | $0.7632 | [GL3549](https://jlcpcb.com/partdetail/10622-GL3549/C10083) |
| **R6, R7** | 1K Resistor | 0201 | 20 | $0.050 | [0201WMF1001TEE](https://jlcpcb.com/partdetail/259895-0201WMF1001TEE/C270365) |
| **R8, R10, R12, R14** | 100 Ohm Resistor | 0201 | 20 | $0.056 | [RC01W1000FT](https://jlcpcb.com/partdetail/288566-RC01W1000FT/C304499) |
| **R9, R11, R13, R15** | 10K Resistor | 0201 | 20 | $0.086 | [CR0201FH1002G](https://jlcpcb.com/partdetail/LIZElec-CR0201FH1002G/C100126) |
| **R1_1, R2_1** | 10K / 100 Ohm | 0805 | 6 | $0.5364 | [FSMD050_0805R](https://jlcpcb.com/partdetail/FuzetecTech-FSMD050_0805R/C181350) |
| **U1** | MT3608 Boost Regulator | SOT-23-6 | 5 | $0.5665 | [MT3608](https://jlcpcb.com/partdetail/XI_AN_AerosemiTech-MT3608/C84817) |
| **U2** | AP63203WU Buck Regulator | TSOT-23-6 | 2 | $2.2268 | [AP63203QWU7](https://jlcpcb.com/partdetail/DiodesIncorporated-AP63203QWU7/C5248536) |
| **U3** | MPU-6050 6-Axis IMU Sensor | QFN-24 | 2 | $29.0122 | [MPU6050](https://jlcpcb.com/partdetail/TDKInvenSense-MPU6050/C24112) |
| **U4** | BMP280 Barometric Pressure Sensor | LGA-8 | 2 | $5.2442 | [BMP388 / BMP280](https://jlcpcb.com/partdetail/BoschSensortec-BMP388/C779278) |
| **U5** | ESP32-S3-WROOM-1 Wi-Fi/BT MCU | Module | 2 | $10.327 | [ESP32_S3_WROOM_1N16R8](https://jlcpcb.com/partdetail/3198300-ESP32_S3_WROOM_1N16R8/C2913202) |
| **J1** | USB Type-C Receptacle 16P | USB-C | - | - | Hand Assembly / Manual |
| **J2** | Pin Header Connector | JST-EH 2.5mm | - | - | Through Hole |
| **M1, M2, M3, M4** | Motor Drive Outputs | 1x02 Pin Header | - | - | Through Hole |
| **SW1, SW2** | Push Button Switches | PTS810 | - | - | SMT / Manual |

---






### Schematic

<img width="1197" height="752" alt="Screenshot 2026-08-05 221707" src="https://github.com/user-attachments/assets/46dac1fd-04a3-44be-b418-202bdf7c4fd5" />


###  PCB Design

<img width="750" height="637" alt="Screenshot 2026-08-05 223850" src="https://github.com/user-attachments/assets/2289d952-7a03-4c28-8be4-af8657073219" />
<img width="1007" height="785" alt="Screenshot 2026-08-05 223902" src="https://github.com/user-attachments/assets/2cc4119f-5651-4195-bb46-a5e33a5a692a" />


###  3D Design
<img width="771" height="492" alt="Screenshot 2026-08-05 230335" src="https://github.com/user-attachments/assets/c9eb69f7-c460-4eeb-a221-6ebcf3850040" />
<img width="767" height="660" alt="Screenshot 2026-08-05 230349" src="https://github.com/user-attachments/assets/d9a66ef6-14eb-466c-956e-3503fcb1c35c" />

