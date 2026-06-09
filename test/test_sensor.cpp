/**
 * Unit-Tests für ESP32 Sensor-Modul
 * Läuft im PlatformIO Test-Framework
 */

#include <unity.h>

// Test: Temperaturwert plausibel
void test_temperature_range(void)
{
  float temp = 22.5; // simulierter Wert
  TEST_ASSERT_TRUE(temp > -40.0 && temp < 85.0);
}

// Test: JSON Format
void test_payload_format(void)
{
  float temp = 22.5;
  float hum = 60.0;
  char payload[64];
  snprintf(payload, 64, "{\"temp\":%.1f,\"hum\":%.1f}", temp, hum);

  TEST_ASSERT_TRUE(strstr(payload, "\"temp\"") != NULL);
  TEST_ASSERT_TRUE(strstr(payload, "\"hum\"") != NULL);
  TEST_ASSERT_TRUE(strstr(payload, "22.5") != NULL);
}

void setup()
{
  UNITY_BEGIN();
  RUN_TEST(test_temperature_range);
  RUN_TEST(test_payload_format);
  UNITY_END();
}

void loop() {}
