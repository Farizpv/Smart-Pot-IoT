# 🌱 Smart Pot – IoT-Based Auto-Watering Plant System

An intelligent, self-watering plant system using NodeMCU ESP8266 and Blynk IoT. 
It monitors real-time soil moisture levels and waters the plant when needed — all visible on an OLED screen and controllable via a mobile app.

---

## 🚀 Features

- 🌿 Real-time soil moisture monitoring
- 💧 Auto-watering when moisture < 40%
- 🔁 10-minute cooldown timer to prevent pump burnout
- 📟 OLED display showing moisture percentage & pump status
- 📲 Blynk IoT integration for live updates, notifications, and remote pump control
- 🔌 Powered via USB-C and 2xAA battery housing

---

## 🔧 Components Used

| Component                 | Quantity |
|---------------------------|----------|
| NodeMCU ESP8266           |    1     |
| M335 Soil Moisture Sensor |    1     |
| SSD1306 OLED Display      |    1     |
| 2-Channel Relay           |    1     |
| Mini Water Pump           |    1     |
| 2xAA Battery Holder       |    1     |
| Breadboard + Jumper Wires | As needed|

---

## 🧠 How It Works

1. **Soil moisture** is read via the M335 analog sensor.
2. If moisture level < 40%, the relay triggers the water pump.
3. Pump stops when moisture rises above 40%.
4. A **10-minute timer** prevents overwatering and protects the motor.
5. OLED shows moisture % and whether the pump is ON or OFF.
6. Blynk app receives push notifications and lets users:
   - Monitor live sensor data
   - Manually trigger watering
   - Tracks Moisture level history
   - Can track the number of times total watered and reset the count

---

## 🖥️ File Structure

Smart-Pot-IoT/
├── SmartPot.ino # Arduino code for ESP8266
├── simulation/
│ ├── diagram.json # Wokwi circuit diagram (simulated on ESP32)
│ └── wokwi-project.txt # Wokwi project info
├── libraries.txt # Required Arduino libraries
└── README.md # This documentation file

---

## 🔌 Libraries Used

Adafruit GFX Library - #include <Adafruit_GFX.h>          # For OLED graphics rendering
Adafruit SSD1306     - #include <Adafruit_SSD1306.h>      # For SSD1306 OLED display
ESP8266 WiFi	      - #include <ESP8266WiFi.h>           # For WiFi connection of ESP
Blynk                - #include <BlynkSimpleEsp8266.h>    # For IoT notifications and remote control (ESP8266-compatible)
EEPROM               - #include <EEPROM.h>                # For storing water count in the EEPROM memory

---

## 🌐 Simulation

> Since Wokwi doesn't support ESP8266, the circuit was simulated using ESP32:
- [Simulate on Wokwi](https://wokwi.com)

---

## ⚙️ How to Run

### 1. Install Libraries in Arduino IDE:
- Adafruit SSD1306
- Adafruit GFX
- Blynk (ESP8266-compatible version)

### 2. Upload Code:
- Open `sketch.ino` in Arduino IDE
- Select **Board: NodeMCU 1.0 (ESP8266)**
- Connect and upload

### 3. Configure Blynk:
- Update `auth` token, `WiFi SSID`, and `password` in the sketch.
- Use Blynk app with a button widget (for manual watering) and display widgets.

---

## 🧠 Creator

**👨‍💻 Fariz PV**  
> Passionate about IoT, automation, and building cool stuff that helps people!  
> 🌍 [LinkedIn](https://www.linkedin.com/in/muhammed-fariz-pv-3b9a22209/) | 📫 farizpv1001@gmail.com

---

## 🪴 Inspiration

> A simple step toward automating plant care and smart gardening. Because even plants deserve smart tech 😄

---

