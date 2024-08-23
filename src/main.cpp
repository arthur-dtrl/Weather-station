#include "Display.h"
#include "JsonRead.h"
#include "WeatherAPI.h"
#include "params.h"
#include <Arduino.h>



parameters params = {"", 0, 0, 0, 1, 0, 0, "", 0, 0, 0, 0};

void printParams(parameters &params) {
  Serial.println("Location: " + String(params.location));
  Serial.println("Time: " + String(params.hour) + ":" + String(params.minutes));
  Serial.println("Temperature: " + String(params.temp));
  Serial.println("Is day: " + String(params.is_day));
  Serial.println("Condition: " + String(params.condition));
  Serial.println("Wind speed: " + String(params.wind_speed));
  Serial.println("Wind direction: " + String(params.wind_dir));
  Serial.println("Pressure: " + String(params.pressure));
  Serial.println("Humidity: " + String(params.humidity));
  Serial.println("Feels like: " + String(params.ftemp));
  Serial.println("UV: " + String(params.uv));
}
void touchISR() {
  if (!is_on) {
    analogWrite(LED_PIN,255);
    is_on = true ;
  }
  else if (is_on){
    analogWrite(LED_PIN,0);
    is_on = false;
  }
}
void setup() {
  Serial.begin(115200);

  pinMode(TOUCH_IRQ, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  analogWrite(LED_PIN,255);
  attachInterrupt(digitalPinToInterrupt(TOUCH_IRQ), touchISR, RISING);

  TFTInit();

  WiFiSync();
}

void loop() {
  String Json = APIRequest(APIKEY, CITY);
  if (Json.length() > 1) {
    readJsonString(Json, &params);
    printParams(params);
  } else {
    Serial.println("Error fetching API");
  }
  draw(&params);
  delay(60000);
}
