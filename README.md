# ESP32 Temperatursensor mit MQTT

Embedded IoT-Projekt: ESP32 + DHT22 (+ MQTT)

## Features
- Temperatur & Luftfeuchtigkeit (DHT22)
- MQTT-Publish alle 30s (JSON)
- WiFi-Verbindung mit Auto-Reconnect
- CI: automatischer Build + Lint + Tests

## Hardware
- ESP32 Dev Board
- DHT22 Sensor
- LED (Status)

## CI/CD
```yaml
# GitHub Actions: automatischer Build bei jedem Push
# PlattformIO + cppcheck static analysis
```

## Schaltplan
```
ESP32        DHT22
─────        ─────
3.3V   ────  VCC
GND    ────  GND
GPIO4  ────  DATA
```

## Portfolio-Wert
✅ Embedded C++ (Arduino/ESP-IDF)
✅ IoT (WiFi + MQTT)
✅ CI/CD Pipeline (GitHub Actions)
✅ Hardware-Integration
