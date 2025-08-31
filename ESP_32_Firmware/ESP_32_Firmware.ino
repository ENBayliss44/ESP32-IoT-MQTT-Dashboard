#include <WiFi.h>
#include <PubSubClient.h>
#include "secure.h"

/*
// Replace with your Wi-Fi and MQTT details and implement in secure.h
const char* WIFI_SSID = "";
const char* WIFI_PASSWORD = "";
const char* MQTT_SERVER = "192.168.1.xxx"; // Your broker's IP
*/


WiFiClient wifiClient;
PubSubClient mqtt(wifiClient);

unsigned long lastPublish = 0;

// MQTT error state decoding
String mqttStateToString(int state) {
  switch(state) {
    case 0: return "Connection accepted";
    case 1: return "Refused - unacceptable protocol version";
    case 2: return "Refused - identifier rejected";
    case 3: return "Refused - server unavailable";
    case 4: return "Refused - bad user name or password";
    case 5: return "Refused - not authorized";
    default: {
      String s = "Unknown/Lib error: ";
      s += String(state);
      return s;
    }
  }
}

// Build a short, unique client ID from MAC (no ":" chars)
String makeClientId() {
  String mac = WiFi.macAddress();
  mac.replace(":", "");
  String id = "ESP32-" + mac;
  // Old MQTT brokers sometimes require <=23 chars — trim to be safe
  if (id.length() > 23) id = id.substring(0, 23);
  return id;
}

void connectWiFi() {
  Serial.print("WiFi: connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  unsigned long start = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - start < 20000) {
    Serial.print(".");
    delay(500);
  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi connected!");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\nWiFi connect FAILED");
  }
}

void mqttReconnect() {
  if (WiFi.status() != WL_CONNECTED) {
    connectWiFi();
    if (WiFi.status() != WL_CONNECTED) return;
  }

  while (!mqtt.connected()) {
    String clientId = makeClientId();
    Serial.print("Trying MQTT connect with ID: ");
    Serial.println(clientId);

    // If your broker needs username/password, use:
    // if (mqtt.connect(clientId.c_str(), "user", "pass")) { ... }
    if (mqtt.connect(clientId.c_str())) {
      Serial.println("MQTT connected!");
      // mqtt.subscribe("some/topic"); // subscribe if needed
    } else {
      int st = mqtt.state();
      Serial.print("MQTT connect failed, state=");
      Serial.print(st);
      Serial.print(" -> ");
      Serial.println(mqttStateToString(st));
      // If identifier rejected (state==2), try a slightly different id next loop
      delay(3000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  delay(100);
  connectWiFi();
  mqtt.setServer(mqttServer, mqttPort);
  mqttReconnect();
}

void loop() {
  if (!mqtt.connected()) mqttReconnect();
  mqtt.loop(); // important for keepalive & incoming messages

  unsigned long now = millis();
  if (now - lastPublish > 5000) {
    lastPublish = now;
    float temperature = random(200, 300) / 10.0; // replace with your sensor
    char buf[16];
    snprintf(buf, sizeof(buf), "%.2f", temperature);
    bool ok = mqtt.publish("sensors/temp", buf);
    Serial.print("Published ");
    Serial.print(buf);
    Serial.print(" -> ");
    Serial.println(ok ? "OK" : "FAILED");
  }
}
