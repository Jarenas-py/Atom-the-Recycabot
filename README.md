# 🤖 Atom the Recycabot - ESP32 Sumo-Bot

**Atom the Recycabot** is a dual-mode Sumo-Bot powered by an ESP32 microcontroller. It features an autonomous battle mode using ultrasonic sensors for opponent detection and a manual control mode via Bluetooth using the Dabble smartphone application.

## 🌟 Features

* **Dual Operation Modes:**
    * **🦾 Automatic Mode:** Autonomously detects opponents within a 62cm range using an ultrasonic sensor and engages by charging forward.
    * **🎮 Manual Mode:** Remote control via Bluetooth using the Dabble Gamepad interface.
* **Real-time Feedback:** LED indicators to show the current active mode.
* **Mobile Integration:** Seamless connection with the Dabble app (IOS/Android).

## 🛠️ Hardware Components

* **Microcontroller:** ESP32 Development Board
* **Motor Driver:** L298N
* **Motors:** 2x DC Motors (12V, 250 RPM)
* **Sensors:** Ultrasonic Sensor (HC-SR04)
* **Power:** 3x Lithium-Ion Batteries (3.7V, 2200 mAh each) connected in series (~11.1V)
* **Chassis:** Custom Sintra board and metal plate construction
* **Input/Output:**
    * 2x Tactile Push Buttons (Mode Selection)
    * 2x LEDs (Red/Blue for Mode Indication)
    * SPDT Power Switch

## 🚀 Installation & Setup

### 1. Software Requirements
* **Arduino IDE:** Download and install to the version specified in the documentation.
* **ESP32 Board Manager:** Install the ESP32 board support in Arduino IDE.
* **DabbleESP32 Library:** Install this library via the Arduino Library Manager to enable Bluetooth control.
* **Dabble App:** Download on your smartphone ([Google Play](https://play.google.com/store/apps/details?id=io.dabbleapp) / [App Store](https://apps.apple.com/us/app/dabble-bluetooth-controller/id1472734455)).

### 2. Wiring and Pin Configuration
Please refer to the diagrams below for detailed connections.

### 3. Uploading Code
1.  Open `atomRecycabot_SourceCode.ino` in Arduino IDE.
2.  Select your board: **Tools > Board > DOIT ESP32 DEVKIT V1** (or your specific model).
3.  Select the correct Port.
4.  Click **Upload**.

## 🕹️ How to Use

1.  **Power On:** Turn on the SPDT switch to power the bot.
2.  **Select Mode:**
    * Press the **Auto Button (Pin 18)** to enter Autonomous Mode. The Auto LED (Pin 21) will light up.
    * Press the **Manual Button (Pin 13)** to enter Manual Mode. The Manual LED (Pin 22) will light up.
3.  **Manual Control:**
    * Open the Dabble App and connect to the Bluetooth device named **"SumoBot_Manual"**.
    * Select the "Gamepad" module.
    * Use the arrow keys to drive Atom.

## 👥 Authors

* **Joseph C. Arenas**
* **Adriene Cyruz Estrada**
* **Geo Kentzer Gutierrez**
* **Lian Gil B. Pacis**
* **Jordan Recaña**

## 📄 License

This project is open-source and available under the [MIT License](LICENSE).
