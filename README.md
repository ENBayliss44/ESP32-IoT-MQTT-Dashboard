
# ESP32 IoT Dashboard Project

![GitHub Repo Size](https://img.shields.io/github/repo-size/ENBayliss44/ESP32-IoT-MQTT-Dashboard)
![GitHub stars](https://img.shields.io/github/stars/ENBayliss44/ESP32-IoT-MQTT-Dashboard?style=social)

## Overview

This project demonstrates an **end-to-end IoT system** using an ESP32-WROOM-32 dev board, I2C Temperature Sensor, MQTT protocol, and a Node-RED dashboard.  
The system reads sensor data from the temperature sensor via the ESP32, publishes it to a local MQTT broker (Mosquitto), and displays it in real-time on a web dashboard. Historical data is also recorded for analysis.

**Key Goals:**
- Learn and demonstrate IoT concepts, MQTT messaging, and embedded system integration.

## Features

- ESP32 SoC publishes sensor data (temperature) over MQTT.
- Local Mosquitto MQTT broker receives and distributes messages.
- Node-RED dashboard visualizes data using:
  - **Gauges** for real-time values
  - **Line charts** for historical trends
- Secure credentials handled via a local `secure.h` file (ignored in GitHub).

## Repo Structure
- `ESP_32_Firmware/` -> ESP32 source code
- `server/` -> MQTT broker config + Node-RED flows
- `.gitignore` -> Prevents committing secrets/build files
- `LICENSE` -> Apache 2.0 License
- `README.md` -> This file

## Getting Started

### 1. ESP32 Firmware

1. Install [Arduino IDE](https://www.arduino.cc/en/software).s  
2. Copy your Wi-Fi and MQTT credentials into `ESP_32_Firmware/secure.h`.  
3. Open `ESP_32_Firmware.ino` and upload to your ESP32.  

### 2. MQTT Broker (Mosquitto)

```bash
# Install Mosquitto on Linux
sudo apt install mosquitto mosquitto-clients

# Copy mosquitto.conf from repo and start broker
sudo cp server/mosquitto.conf /etc/mosquitto/mosquitto.conf
sudo systemctl restart mosquitto

# Verify it's listening on port 1883
sudo lsof -iTCP -sTCP:LISTEN -n -P | grep mosquitto
```

### 3. Node-RED Dashboard

```bash
# Install Node-RED globally
sudo npm install -g node-red

# Install dashboard nodes
cd server
npm install node-red-dashboard
```

#### 3.1. Start Node-RED
```bash
node-red
```

#### 3.2. Import flows: Menu -> Import -> Clipboard -> Paste flows.json

#### 3.3. Open dashboard: http://localhost:1880/ui

## Security Notes

Do not commit secure.h as it contains your Wi-Fi and MQTT credentials.

.gitignore ensures sensitive files and build artifacts are not uploaded to GitHub.

## Contributing
Contributions are welcome! Please follow these guidelines:

Fork the repository.

Create a branch for your feature/bug fix.

Commit changes with clear messages.

Open a pull request describing your changes.

## To-Do

Implement I2C temp sensor (Currently simulating using psuedorandom data)

## Future Enhancements

Add additional sensors (humidity, pressure, motion).

Implement remote access using secure VPN or cloud MQTT broker.

Expand dashboard with multiple charts and alerts.

Integrate data logging to a local database for analytics.

## Author

Edward Bayliss - Mechatronics Engineer

## License

This project is licensed under the **Apache License 2.0**. See the [LICENSE](LICENSE) file for details.

