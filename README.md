# 🌱 Smart Pot – IoT-Based Auto-Watering Plant System

An intelligent, self-watering plant system using NodeMCU ESP8266 and Blynk IoT. It monitors real-time soil moisture levels and waters the plant when needed — all visible on an OLED screen and controllable via a mobile app.

---

## 📸 Project Showcase

<p align="center">
  <img src="docs/setup-images/demo.jpg" width="400" title="Physical Setup">
</p>

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

| Component           | Quantity |
|---------------------|----------|
| NodeMCU ESP8266     | 1        |
| M335 Soil Moisture Sensor | 1  |
| SSD1306 OLED Display| 1        |
| 2-Channel Relay     | 1        |
| Mini Water Pump     | 1        |
| 2xAA Battery Holder | 1        |
| Breadboard + Jumper Wires | As needed |

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

---

## 🖥️ File Structure

