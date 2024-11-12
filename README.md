# IoT Environmental Monitoring System

This project is an IoT-based environmental monitoring system using ESP32, DHT22 sensor, and Blynk. It monitors temperature, humidity, light, and motion in real-time, with data sent to Blynk for remote visualization and control.

## Features

- **Sensors**: Monitors temperature, humidity (DHT22), light intensity (LDR), and motion (PIR).
- **Remote Monitoring**: Real-time data and controls through Blynk app.
- **Automated Controls**: Relay toggles lights based on ambient light; LEDs indicate motion.

## Components

- **Hardware**: ESP32, DHT22, LDR, PIR, Relay, LEDs.
- **Libraries**: Blynk, DHT, PubSubClient, WiFi.

## Setup

1. **Clone Repository**:
   ```bash
   git clone https://github.com/yourusername/IoT-Environmental-Monitoring.git
2. **Install Libraries**: Install Blynk, DHT, PubSubClient in Arduino IDE.
3. **Configure Blynk**: Download the Blynk app, create a project, and get your Auth Token.
Edit Code: Update Wi-Fi and Auth Token:
cpp
Copy code
const char* ssid = "Your_WiFi_SSID";
const char* password = "Your_WiFi_Password";
#define BLYNK_AUTH_TOKEN "Your_Blynk_Token"
Upload Code: Connect ESP32 and upload code.
Pin Connections
DHT22 to GPIO32, PIR to GPIO5, LEDs to GPIO18/19/21, Relay to GPIO23, LDR to GPIO34.
Usage
After deployment, monitor data in Blynk. Relay and LEDs adjust automatically based on sensor inputs.
