/**
 * ESP32 Temperatursensor mit MQTT
 * -------------------------------
 * Liest DHT22 Sensor aus und sendet Daten via MQTT
 * Für IoT / Embedded-Portfolio
 */

#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

// === Konfiguration ===
#define DHTPIN 4
#define DHTTYPE DHT22
#define LED_PIN 2

const char *ssid = "WIFI_SSID";
const char *password = "WIFI_PASS";
const char *mqtt_server = "192.168.1.100";
const int mqtt_port = 1883;
const char *mqtt_topic = "sensor/temperature";

// === Globale Objekte ===
DHT dht(DHTPIN, DHTTYPE);
WiFiClient espClient;
PubSubClient client(espClient);

// === Forward Declarations ===
void connectWiFi();
void connectMQTT();
void sendSensorData();

void setup()
{
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  dht.begin();

  connectWiFi();
  client.setServer(mqtt_server, mqtt_port);
}

void loop()
{
  if (!client.connected())
  {
    connectMQTT();
  }
  client.loop();

  sendSensorData();
  delay(30000); // alle 30s senden
}

void connectWiFi()
{
  Serial.print("🔌 Verbinde mit WiFi");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n✅ WiFi verbunden! IP: " + WiFi.localIP().toString());
}

void connectMQTT()
{
  while (!client.connected())
  {
    Serial.print("📡 Verbinde mit MQTT...");
    if (client.connect("ESP32_Sensor"))
    {
      Serial.println("✅ verbunden!");
    }
    else
    {
      Serial.print("❌ fehlgeschlagen (");
      Serial.print(client.state());
      Serial.println("). Retry in 5s...");
      delay(5000);
    }
  }
}

void sendSensorData()
{
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  if (isnan(temp) || isnan(hum))
  {
    Serial.println("⚠️ Sensorfehler – keine Daten");
    return;
  }

  char payload[64];
  snprintf(payload, 64, "{\"temp\":%.1f,\"hum\":%.1f}", temp, hum);

  if (client.publish(mqtt_topic, payload))
  {
    digitalWrite(LED_PIN, HIGH);
    Serial.print("📤 Gesendet: ");
    Serial.println(payload);
    delay(100);
    digitalWrite(LED_PIN, LOW);
  }
  else
  {
    Serial.println("❌ Fehler beim Senden");
  }
}
