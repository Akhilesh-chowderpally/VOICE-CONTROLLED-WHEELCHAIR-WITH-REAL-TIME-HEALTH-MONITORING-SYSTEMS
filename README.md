# 🚀 Voice-Controlled Wheelchair with Real-Time Health Monitoring

An **assistive mobility system** that combines **offline voice commands** and **joystick control** with **wireless telemetry**, plus hooks for **real-time vitals tracking and alerts**.  
Built around **Arduino boards, NRF24L01 radios, and an H-bridge motor driver** for smooth, safe navigation indoors and out.

---

## 🌟 About The Project
This project aims to make mobility more **independent and safer** by enabling:

- 🎤 **Hands-free control** with offline speech recognition.  
- 🎮 **Reliable manual joystick fallback** for safety.  
- ❤️ **Health monitoring hooks** for proactive care.  
- ⚡ **Low-latency wireless link** via 2.4 GHz NRF24L01.  

Offline speech recognition avoids cloud latency and connectivity issues. The RF link ensures **responsive, low-power control**, while the build tackles **RF stability, motor driving, and noise-tolerant voice input** using **dual-mic ASR and SPI-based radios with proper decoupling**.

---

## 🛠️ Built With
- **Arduino Nano (TX)** + **Arduino Uno (RX)** → modular control and motor drive.  
- **DFRobot Offline Voice Recognition Module** (UART/I2C, 121 fixed + 17 custom commands).  
- **NRF24L01 transceivers** (3.3V, hardware SPI, CE/CSN GPIO) with bulk decoupling.  
- **L298N dual H-bridge** + **12V geared DC motors** (PWM speed, forward/reverse, braking).  
- **C++ (Arduino)** with **PlatformIO / Arduino IDE**.  

---

## 📺 Demo
🎥 Click the preview below to watch the full video demonstration on YouTube:  

[![Watch the demo](https://img.youtube.com/vi/YOUR_VIDEO_ID/0.jpg)](https://youtube.com/shorts/gs5IsapF_Z0?feature=share)

---

## 📊 System Block Diagram

Transmitter (Arduino Nano)
├── Joystick
├── Voice Recognition Module
└── NRF24L01 (TX)
↓ 2.4GHz Link
Receiver (Arduino Uno)
├── NRF24L01 (RX)
├── L298N Motor Driver → DC Motors
└── Health Sensors (I2C / UART bus)



---

## ⚡ Features
- Dual control: **Voice + Joystick**.  
- **Offline voice recognition** (no internet needed).  
- **Bidirectional RF telemetry** with NRF24L01.  
- **Motor safety features**: braking + PWM speed control.  
- Expandable: add **heart rate, SpO₂, or ECG sensors** for **real-time health monitoring**.  

---

## 📂 Repository Structure
```bash
📦 voice-wheelchair
 ┣ 📂 transmitter_code   # Arduino Nano (Voice + Joystick + TX)
 ┣ 📂 receiver_code      # Arduino Uno (Motors + RX + Health Sensors)
 ┣ 📂 docs               # Block diagrams, schematics, images
 ┣ 📜 LICENSE
 ┣ 📜 README.md
 ┗ 📜 requirements.txt   # PlatformIO / Arduino libs


