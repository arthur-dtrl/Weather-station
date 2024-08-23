#ifndef JSON_READ_H
#define JSON_READ_H
#include "params.h"
#include "WiFiSync.h"
#include <ArduinoJson.h>
int readJsonString(String jsonString, parameters *params);
#endif