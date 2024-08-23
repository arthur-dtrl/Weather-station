#include "WeatherAPI.h"

#define DEBUG

HTTPClient http;

String APIRequest(const char *apiKey, const char *city) {
  String url = "http://api.weatherapi.com/v1/current.json?q=";
  url += city;
  url += "&key=";
  url += apiKey;

  http.begin(url);

  int httpCode = http.GET();
  Serial.println(httpCode);
  if (httpCode > 0) {
    String payload = http.getString();
#ifdef DEBUG

    Serial.println(payload);
#endif
    http.end();
    return payload;
  } else {
    Serial.println("Error on HTTP request");
    http.end();
    return "";
  }
}
