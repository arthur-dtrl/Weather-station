

#include "Display.h"

TFT_eSPI tft = TFT_eSPI();

// ICON SPRITES
TFT_eSprite time_sprite = TFT_eSprite(&tft);
TFT_eSprite weather_sprite = TFT_eSprite(&tft);
TFT_eSprite wind_sprite = TFT_eSprite(&tft);
TFT_eSprite thermometer_sprite = TFT_eSprite(&tft);
TFT_eSprite humidity_sprite = TFT_eSprite(&tft);
TFT_eSprite pressure_sprite = TFT_eSprite(&tft);
TFT_eSprite UV_sprite = TFT_eSprite(&tft);

// TEXT SPRITES
TFT_eSprite text_location_sprite = TFT_eSprite(&tft);

bool is_on = false;

void TFTInit() {
  uint16_t calData[5] = {335, 3504, 370, 3326, 7}; // Calibration data for touch
  tft.init();
  is_on = true;
  tft.setRotation(1);
  tft.setPivot(TFT_HEIGHT / 2 + ICON_SIZE / 2,
               (4 * TFT_WIDTH / 5 + TFT_WIDTH / 2) / 2);
  tft.setTextColor(TFT_DARKGREY, TFT_WHITE);
  tft.setSwapBytes(true);
  tft.setTouch(calData);

  createSprites();
  initDraw();
  initText();
}

void createSprites() {
  // ICON SPRITES
  wind_sprite.createSprite(ICON_SIZE, ICON_SIZE);
  wind_sprite.setSwapBytes(true);
  wind_sprite.setPivot(ICON_SIZE / 2, ICON_SIZE / 2);

  time_sprite.createSprite(ICON_SIZE, ICON_SIZE);
  time_sprite.setSwapBytes(true);

  thermometer_sprite.createSprite(ICON_SIZE, ICON_SIZE);
  thermometer_sprite.setSwapBytes(true);

  weather_sprite.createSprite(ICON_SIZE, ICON_SIZE);
  weather_sprite.setSwapBytes(true);

  humidity_sprite.createSprite(ICON_SIZE, ICON_SIZE);
  humidity_sprite.setSwapBytes(true);

  pressure_sprite.createSprite(ICON_SIZE, ICON_SIZE);
  pressure_sprite.setSwapBytes(true);

  UV_sprite.createSprite(ICON_SIZE, ICON_SIZE);
  UV_sprite.setSwapBytes(true);

  // TEXT SPRITES

  text_location_sprite.createSprite(TEXT_WIDTH, TEXT_HEIGHT);
  text_location_sprite.setSwapBytes(true);
  text_location_sprite.setFreeFont(&FreeSansBold12pt7b);
  text_location_sprite.setTextSize(1);
  text_location_sprite.setTextColor(TFT_DARKGREY, TFT_WHITE);
}
void initText() {

  // TEXT

  text_location_sprite.drawString("Location", 0, 0);
  text_location_sprite.pushSprite(LOC_X, LOC_Y, TFT_BLACK);

  tft.setFreeFont(&FreeSansBold18pt7b);
  tft.setTextSize(1);

  tft.setCursor(TIME_X, TIME_Y);
  tft.print("--:--"); // TIME

  tft.setCursor(TEMP_X, TEMP_Y);
  tft.print("--.-- *C"); // TEMPERATURE

  tft.setCursor(FL_X, FL_Y);
  tft.print("-- *C"); // FEELS LIKE

  tft.setFreeFont(&FreeSansBold12pt7b);
  tft.setCursor(COND_X, COND_Y);
  tft.print("Weather"); // CONDITION

  tft.setCursor(WIND_X, WIND_Y);
  tft.print("--.- km/h"); // WIND

  tft.setCursor(HUM_X, HUM_Y);
  tft.print("--.-%"); // HUMIDITY

  tft.setCursor(PRESS_X, PRESS_Y);
  tft.print("-- mb"); // PRESSURE

  tft.setCursor(UV_X, UV_Y);
  tft.print("index"); // UV
}
void initDraw() {
  tft.fillScreen(TFT_WHITE);
  
  
  wind_sprite.pushImage(0, 0, ICON_SIZE, ICON_SIZE, N);
  wind_sprite.pushSprite(
      TFT_HEIGHT / 2, (4 * TFT_WIDTH / 5 + TFT_WIDTH / 2) / 2 - ICON_SIZE / 2,
      TFT_BLACK);

  time_sprite.pushImage(0, 0, ICON_SIZE, ICON_SIZE, sun);
  time_sprite.pushSprite(5 * TFT_HEIGHT / 6 - ICON_SIZE / 2, 0, TFT_BLACK);

  thermometer_sprite.pushImage(0, 0, ICON_SIZE, ICON_SIZE, thermometer);
  thermometer_sprite.pushSprite(
      0, (TFT_WIDTH / 5 + TFT_WIDTH / 2) / 2 - ICON_SIZE / 2, TFT_BLACK);
  thermometer_sprite.pushSprite(
      0, (4 * TFT_WIDTH / 5 + TFT_WIDTH / 2) / 2 - ICON_SIZE / 2, TFT_BLACK);

  weather_sprite.pushImage(0, 0, ICON_SIZE, ICON_SIZE, sun);
  weather_sprite.pushSprite(TFT_HEIGHT / 2,
                            (TFT_WIDTH / 5 + TFT_WIDTH / 2) / 2 - ICON_SIZE / 2,
                            TFT_BLACK);

  humidity_sprite.pushImage(0, 0, ICON_SIZE, ICON_SIZE, humidity);
  humidity_sprite.pushSprite(0, 4 * TFT_WIDTH / 5, TFT_BLACK);

  pressure_sprite.pushImage(0, 0, ICON_SIZE, ICON_SIZE, pressure);
  pressure_sprite.pushSprite(TFT_HEIGHT / 3, 4 * TFT_WIDTH / 5, TFT_BLACK);

  UV_sprite.pushImage(0, 0, ICON_SIZE, ICON_SIZE, uv);
  UV_sprite.pushSprite(2 * TFT_HEIGHT / 3, 4 * TFT_WIDTH / 5, TFT_BLACK);
  
}
void draw(parameters *params) {
  /*ICONS*/

  // DAY/NIGHT

  time_sprite.fillSprite(TFT_WHITE);
  time_sprite.pushSprite(5 * TFT_HEIGHT / 6 - ICON_SIZE / 2, 0, TFT_BLACK);
  time_sprite.pushImage(0, 0, ICON_SIZE, ICON_SIZE,
                        (params->is_day ? sun : moon));

  time_sprite.pushSprite(5 * TFT_HEIGHT / 6 - ICON_SIZE / 2, 0, TFT_BLACK);

  tft.setFreeFont(&FreeSansBold18pt7b);

  // LOCATION
  text_location_sprite.fillSprite(TFT_WHITE);
  text_location_sprite.drawString(String(params->location), 0, 0);
  text_location_sprite.pushSprite(LOC_X, LOC_Y, TFT_BLACK);
  // TIME
  tft.fillRect(TIME_X, TIME_Y - 50, 100, 60, TFT_WHITE);
  tft.setCursor(TIME_X, TIME_Y);
  tft.print(String(params->hour) + ":" + (params->minutes < 10 ? "0" : "") +
            String(params->minutes));
  // TEMPERATURE

  tft.fillRect(TEMP_X, TEMP_Y - 50, 150, 60, TFT_WHITE);
  tft.setCursor(TEMP_X, TEMP_Y);
  tft.print(String(params->temp) + " *C");

  // FEELS LIKE

  tft.fillRect(FL_X, FL_Y - 50, 100, 60, TFT_WHITE);
  tft.setCursor(FL_X, FL_Y);
  tft.print(String(params->ftemp) + " *C");

  tft.setFreeFont(&FreeSansBold12pt7b);

  // CONDITION
  weather_sprite.fillSprite(TFT_WHITE);
  weather_sprite.pushSprite(TFT_HEIGHT / 2,
                            (TFT_WIDTH / 5 + TFT_WIDTH / 2) / 2 - ICON_SIZE / 2,
                            TFT_BLACK);
  tft.fillRect(COND_X, COND_Y - 50, 200, 60, TFT_WHITE);
  tft.setCursor(COND_X, COND_Y);

  switch (params->condition) {
  case 1000:
  case 1003:
    weather_sprite.pushImage(0, 0, ICON_SIZE, ICON_SIZE,
                             (params->is_day ? sun : moon));
    tft.print("Clear");
    break;
  case 1006:
  case 1009:
  case 1030:
  case 1135:
  case 1147:

    weather_sprite.pushImage(0, 0, ICON_SIZE, ICON_SIZE, cloudy);
    tft.print("Cloudy");
    break;
  case 1063:
  case 1072:
  case 1150:
  case 1153:
  case 1168:
  case 1171:
  case 1180:
  case 1183:
  case 1186:
  case 1189:
  case 1192:
  case 1195:
  case 1198:
  case 1201:
  case 1204:
  case 1207:
  case 1240:
  case 1243:
  case 1246:
  case 1249:
  case 1252:
    weather_sprite.pushImage(0, 0, ICON_SIZE, ICON_SIZE, rain);
    tft.print("Rain");
    break;
  case 1066:
  case 1069:
  case 1114:
  case 1117:
  case 1210:
  case 1213:
  case 1216:
  case 1219:
  case 1222:
  case 1225:
  case 1237:
  case 1255:
  case 1258:
  case 1261:
  case 1264:
    weather_sprite.pushImage(0, 0, ICON_SIZE, ICON_SIZE, snow);
    tft.print("Snow");
  case 1087:
  case 1273:
  case 1276:
  case 1279:
  case 1282:
    weather_sprite.pushImage(0, 0, ICON_SIZE, ICON_SIZE, thunderstorm);
    tft.print("Thunderstorm");
  default:
    break;
  }
  weather_sprite.pushSprite(TFT_HEIGHT / 2,
                            (TFT_WIDTH / 5 + TFT_WIDTH / 2) / 2 - ICON_SIZE / 2,
                            TFT_BLACK);

  // WIND
  wind_sprite.deleteSprite();
  wind_sprite.createSprite(ICON_SIZE, ICON_SIZE);
  wind_sprite.setSwapBytes(false);
  wind_sprite.setPivot(ICON_SIZE / 2, ICON_SIZE / 2);
  tft.fillRect(TFT_HEIGHT / 2,
               (4 * TFT_WIDTH / 5 + TFT_WIDTH / 2) / 2 - ICON_SIZE / 2,
               ICON_SIZE, ICON_SIZE, TFT_WHITE);
  wind_sprite.pushImage(0, 0, ICON_SIZE, ICON_SIZE, N);

  switch (params->wind_dir[0]) {
  case 'N':
    switch (params->wind_dir[1]) {
    case 'E':
      wind_sprite.pushRotated(45, TFT_BLACK);
      break;
    case 'W':
      wind_sprite.pushRotated(315, TFT_BLACK);
      break;
    case '\0':
      wind_sprite.pushSprite(TFT_HEIGHT / 2,
                             (4 * TFT_WIDTH / 5 + TFT_WIDTH / 2) / 2 -
                                 ICON_SIZE / 2);
      break;
    case 'N':
      switch (params->wind_dir[2]) {
      case 'E':
        wind_sprite.pushRotated(22.5, TFT_BLACK);
        break;
      case 'W':
        wind_sprite.pushRotated(337.5, TFT_BLACK);
        break;
      default:
        break;
      }
    }
    break;
  case 'E':
    switch (params->wind_dir[1]) {
    case 'N':
      wind_sprite.pushRotated(67.5, TFT_BLACK);
      break;
    case 'S':
      wind_sprite.pushRotated(112.5, TFT_BLACK);
      break;
    case '\0':
      wind_sprite.pushRotated(90, TFT_BLACK);
      break;
    }
    break;
  case 'S':

    switch (params->wind_dir[1]) {
    case 'E':
      wind_sprite.pushRotated(135, TFT_BLACK);
      break;
    case 'W':
      wind_sprite.pushRotated(225, TFT_BLACK);
      break;
    case '\0':
      wind_sprite.pushRotated(180, TFT_BLACK);
      break;
    case 'S':
      switch (params->wind_dir[2]) {
      case 'E':
        wind_sprite.pushRotated(157.5, TFT_BLACK);
        break;
      case 'W':
        wind_sprite.pushRotated(202.5, TFT_BLACK);

        break;
      }
    }
    break;
  case 'W':
    switch (params->wind_dir[1]) {
    case 'N':
      wind_sprite.pushRotated(292.5, TFT_BLACK);
      break;
    case 'S':
      wind_sprite.pushRotated(247.5, TFT_BLACK);
      break;
    case '\0':
      wind_sprite.pushRotated(270, TFT_BLACK);
      break;
    }
    break;
  default:
    break;
  }

  tft.fillRect(WIND_X, WIND_Y - 60, 200, 70, TFT_WHITE);
  tft.setCursor(WIND_X, WIND_Y);
  tft.print(String(params->wind_speed) + " km/h");

  tft.fillRect(HUM_X, HUM_Y - 25, 70, 50, TFT_WHITE);
  tft.setCursor(HUM_X, HUM_Y);
  tft.print(String(params->humidity) + " %"); // HUMIDITY

  tft.fillRect(PRESS_X, PRESS_Y - 25, 70, 50, TFT_WHITE);
  tft.setCursor(PRESS_X, PRESS_Y);
  tft.print(params->pressure); // PRESSURE

  tft.fillRect(UV_X, UV_Y - 25, 90, 50, TFT_WHITE);
  tft.setCursor(UV_X, UV_Y);
  tft.print(params->uv); // UV
}