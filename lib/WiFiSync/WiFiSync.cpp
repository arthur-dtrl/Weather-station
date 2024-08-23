#include "WiFiSync.h"

const char *ntpServer = "pool.ntp.org";
const long gmtOffset_sec =
    3600; // Décalage horaire en secondes (ex : GMT+1 = 3600)
const int daylightOffset_sec = 3600; // Offset pour l'heure d'été en secondes

void WiFiSync() {
  WiFi.begin(SSID, PASSWORD);
  delay(2000);
  Serial.println("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to the WiFi network");

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
}