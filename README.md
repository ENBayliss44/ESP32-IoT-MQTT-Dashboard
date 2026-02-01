
# ESP32 IoT Dashboard Project

## Overview

This project demonstrates an end-to-end IoT system using an ESP32-WROOM-32 development board, a DHT11 temperature sensor, MQTT messaging, and a Node-RED web dashboard.

The ESP32 reads temperature data from the sensor, publishes it to a local MQTT broker (Mosquitto), and Node-RED subscribes to the data and visualizes it in real time. Historical values are displayed using charts for trend analysis

## System Architecture
![Architecture](docs/architecture.svg)

ESP32 (DHT11)
↓ MQTT publish (sensors/temp)
Mosquitto Broker
↓ MQTT subscribe
Node-RED
↓
Web Dashboard (Gauge + Chart)

**Key Goals:**
- Demonstrate practical IoT architecture using MQTT
- Integrate embedded firmware with backend services
- Visualize live and historical sensor data

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

1. Install [Arduino IDE](https://www.arduino.cc/en/software)
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

Note: On Windows or macOS, install Mosquitto using the official installer and ensure it is listening on port 1883 with remote access enabled.

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

Note: On Windows or macOS, install node-red using the official installer.

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

## Future Enhancements

Add additional sensors (pressure, motion).

Implement remote access using secure VPN or cloud MQTT broker.

Expand dashboard with multiple charts and alerts.

Integrate data logging to a local database for analytics.

## Author

Edward Bayliss - Mechatronics Engineer

## License

This project is licensed under the **Apache License 2.0**. See the [LICENSE](LICENSE) file for details.

