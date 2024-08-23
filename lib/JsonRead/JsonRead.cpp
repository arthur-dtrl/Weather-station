#include "JsonRead.h"

int readJsonString(String jsonString, parameters *params) {

  // Lire le fichier et le parser

  StaticJsonDocument<1100> doc;

  DeserializationError error = deserializeJson(doc, jsonString);

  if (error) {
    Serial.print("deserializeJson() failed: ");
    Serial.println(error.c_str());
    return 0;
  }
  JsonObject location = doc["location"];
  params->location =
      strndup(location["name"], strlen(location["name"]) * sizeof(char));

  struct tm timeinfo;

  if (!getLocalTime(&timeinfo)) {
    Serial.println("Echec de l'obtention de l'heure locale");
    return -1;
  }
  params->hour = timeinfo.tm_hour;
  params->minutes = timeinfo.tm_min;

  JsonObject current = doc["current"];

  params->temp = current["temp_c"];

  params->is_day = current["is_day"];

  JsonObject current_condition = current["condition"];

  params->condition = current_condition["code"];

  params->wind_speed = current["wind_kph"];
  params->wind_dir =
      strndup(current["wind_dir"], strlen(current["wind_dir"]) * sizeof(char));
  params->pressure = current["pressure_mb"];
  params->humidity = current["humidity"];
  params->ftemp = current["feelslike_c"];
  params->uv = current["uv"];

  return 1;
  // Fermer le fichier
}