#ifndef DISPLAY_H
#define DISPLAY_H

#include "images/icon.h"
#include "params.h"
#include <SPI.h>
#include <TFT_eSPI.h>

// ICON
#define ICON_SIZE 64

/*TEXT SIZES*/

//TFT
#define TEXT_HEIGHT 40
#define TEXT_WIDTH 210
//LOCATION
#define LOC_X 10
#define LOC_Y 20
//TIME
#define TIME_X 240
#define TIME_Y 40
//TEMPERATURE
#define TEMP_X 100
#define TEMP_Y 120
// FEELS LIKE
#define FL_X 100
#define FL_Y 220
// CONDITION
#define COND_X 320
#define COND_Y 120
// WIND
#define WIND_X 320
#define WIND_Y 220
// HUMIDITY
#define HUM_X 80
#define HUM_Y 295
// PRESSURE
#define PRESS_X 240
#define PRESS_Y 295

// UV
#define UV_X 420
#define UV_Y 295

// LED
#define LED_PIN 33

extern bool is_on ;

void createSprites();
void TFTInit();
void initText();
void initDraw();
void draw(parameters *params);


#endif