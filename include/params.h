#ifndef PARAMS_H
#define PARAMS_H

#include <Arduino.h>

typedef struct parameters {
  char *location;
  int hour;
  int minutes;
  float temp;
  int is_day;
  int condition;
  float wind_speed;
  char *wind_dir;
  int pressure;
  int humidity;
  int ftemp;
  int uv;
} parameters;

#endif