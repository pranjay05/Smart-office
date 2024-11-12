#include <Arduino.h>

#define BLYNK_TEMPLATE_ID "TMPL3ea-9_yKn"
#define BLYNK_TEMPLATE_NAME "Smart Office"
#define BLYNK_AUTH_TOKEN "wWTovlfwJ00y-gPNYlJ_eu3D_1QoyGui"

#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>
#include <BlynkSimpleEsp32.h>

// Wi-Fi and Blynk credentials
const char* ssid = "Prithvi";
const char* password = "12345678";

// Blynk Wi-Fi setup
WiFiClient espClient;
PubSubClient client(espClient);

// DHT sensor setup (Temperature and Humidity)
#define DHTPIN 32        // Pin connected to DHT sensor
#define DHTTYPE DHT22    // DHT 22 (AM2302)
DHT dht(DHTPIN, DHTTYPE);

// Pin definitions
const int relayPin = 23;   // Relay for controlling light (LED or Relay)
const int ledPin1 = 18;    // LED1 pin (indicator light)
const int ledPin2 = 19;    // LED2 pin (indicator light)
const int ledPin3 = 21;    // LED3 pin (indicator light)
const int ldrPin = 34;     // LDR pin (Light sensor)
const int motionPin = 5;   // Motion sensor (PIR)

// Set the Blynk virtual pins for different data streams
#define VIRTUAL_PIN_LDR     V1
#define VIRTUAL_PIN_TEMP    V2
#define VIRTUAL_PIN_HUM     V3
#define VIRTUAL_PIN_MOTION  V4
#define VIRTUAL_PIN_RELAY   V5

void setup() {
  // Start serial communication
  Serial.begin(115200);
  // Initialize pins
  pinMode(relayPin, OUTPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(motionPin, INPUT);

  // Start DHT sensor
  dht.begin();

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");

  // Connect to Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, password);
}

void loop() {
  // Blynk run
  Blynk.run();

  // Read LDR value (light sensor)
  int ldrValue = analogRead(ldrPin);

  // Read temperature and humidity
  float temp = dht.readTemperature();
  int temp_int = temp * 10;  // Multiply by 10 for precision
  float hum = dht.readHumidity();
  int hum_int = hum * 10;  // Multiply by 10 for precision

  // Read motion sensor
  int motionDetected = digitalRead(motionPin);

  // Send sensor data to Blynk
  void sendSensorDataToBlynk(int ldrValue, int temp_int, int hum_int, int motionDetected);

  void controlRelay(int ldrValue);

  void controlLEDs(int motionDetected);

  delay(2000);
}

// Function to send sensor data to Blynk
void sendSensorDataToBlynk(int ldrValue, int temp_int, int hum_int, int motionDetected) {
  // Send LDR value to Blynk (virtual pin V1)
  Blynk.virtualWrite(VIRTUAL_PIN_LDR, ldrValue);

  // Send temperature to Blynk (virtual pin V2)
  Blynk.virtualWrite(VIRTUAL_PIN_TEMP, temp_int); // Sending integer (temperature * 10)

  // Send humidity to Blynk (virtual pin V3)
  Blynk.virtualWrite(VIRTUAL_PIN_HUM, hum_int); // Sending integer (humidity * 10)

  // Send motion status to Blynk (virtual pin V4)
  Blynk.virtualWrite(VIRTUAL_PIN_MOTION, motionDetected);
}

// Function to control relay based on LDR value
void controlRelay(int ldrValue) {
  if (ldrValue < 500) {  // If it's dark, turn on the relay (light)
    digitalWrite(relayPin, HIGH);
  } else {  // If it's bright, turn off the relay (light)
    digitalWrite(relayPin, LOW);
  }
}

// Function to control LEDs based on motion sensor
void controlLEDs(int motionDetected) {
  if (motionDetected == HIGH) {
    digitalWrite(ledPin1, HIGH);  // Turn on LED1 if motion is detected
    digitalWrite(ledPin2, HIGH);  // Turn on LED2 if motion is detected
    digitalWrite(ledPin3, HIGH);  // Turn on LED3 if motion is detected
  } else {
    digitalWrite(ledPin1, LOW);   // Turn off LED1 if no motion
    digitalWrite(ledPin2, LOW);   // Turn off LED2 if no motion
    digitalWrite(ledPin3, LOW);   // Turn off LED3 if no motion
  }
}
