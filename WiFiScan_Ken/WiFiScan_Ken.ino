/*
 *  This sketch demonstrates how to scan WiFi networks.
 *  The API is almost the same as with the WiFi Shield library,
 *  the most obvious difference being the different file you need to include:
 */
#include "WiFi.h"

// ESP32 Wrover.
#if !defined(LED_BUILTIN) && !defined(BUILTIN_LED)
#define LED_BUILTIN 27
#define LED_INVERT
#endif // LED_BUILTIN

// ESP32 DoIt DevKit
//#undef  LED_BUILTIN
//#define LED_BUILTIN 2
//#define LED_INVERT
// End ESP32 DoIt DevKit

#ifdef LED_INVERT
const uint8_t   LED_ON  = LOW;
#else
const uint8_t   LED_ON  = HIGH;
#endif // LED_INVERT


void setup()
{
  Serial.begin(115200);

  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.printf(PSTR("LED_BUILTIN %d, LED_ON %s\n"), LED_BUILTIN, LED_ON == HIGH ? "HIGH" : "LOW");

  delay(1000);
  Serial.println("Setup done");
}

void loop()
{
  digitalWrite(LED_BUILTIN, LED_ON);
  Serial.println("scan start");

  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  digitalWrite(LED_BUILTIN, !LED_ON);
  if (n == 0) {
    Serial.println("no networks found");
  } else {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i) {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");
      delay(10);
    }
  }
  Serial.println("");

  // Wait a bit before scanning again
  delay(5000);
}
