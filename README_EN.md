# radar_by_zholgeldi_yerassyl
# Ultrasonic Radar System

This project visualizes real-time data from an ultrasonic sensor using a 180° radar-style interface built with Processing.

## 📦 Features
- 180 servo sweep
- Real-time distance detection
- Glowing radar visual effect
- Object fade-out after detection

## 🧰 Requirements
- Arduino Uno/Nano
- HC-SR04 Ultrasonic Sensor
- Servo Motor
- Processing 3+
- Arduino IDE

## 🛠 Downloads

- [Arduino IDE Download](https://www.arduino.cc/en/software)
- [Processing Download](https://processing.org/download/)


### 🔌 Connection

| Component      | Arduino Pin     |
|----------------|-----------------|
| HC-SR04 Trig   | D10             |
| HC-SR04 Echo   | D11             |
| Servo Motor    | D12             |
| VCC (Sensor & Servo) | 5V       |
| GND (Sensor & Servo) | GND      |

> **Note:** All devices operate at 5V. If the servo draws too much current, consider using an external power source.


## 📂 Folder Structure
- `Arduino/` contains the radar control code for Arduino
- `Processing/` contains the radar visualizer sketch

## 🔌 How to Use
1. Upload `FoXRadarCode` to your Arduino.
2. Open `visualiation_radar` in Processing.
3. Make sure to select the correct `COM` port.
4. Run the sketch and watch the radar in action!

## 🧑‍💻 Author
Yerassyl Zholgeldiyev

## 📄 License
[LICENSE](./LICENSE)

