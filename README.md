# ESP-32 Weather station
This weather station is built using an ESP32-WROOM32 MCU and a LAFVIN ST7796S 4'0 LCD screen. The GUI displays the following : location, time, day/night, real temperature, feels like temperature,  weather condition, wind direction and speed, humidity, atmospheric pressure and UV index. Touching the screen will turn off the backlights which allows the device to operate while lowering the power usage.

## Setting up PlatformIO
Libraries needed:

-bblanchon/ArduinoJson

-bodmer/TFT_eSPI

## Seting up the software
-Create an account on WeatherAPI.com

-Create an API Key

-Put it in the include/config.h file

-fill the config.h file with your WiFi SSID and password, and your location.

## Setting up the screen
In order to use the TFT_eSPI library, you have to select an user setup.
Your user setup should look like this: 
```
#define ST7796_DRIVER

#define TFT_MISO 19
#define TFT_MOSI 23
#define TFT_SCLK 18
#define TFT_CS   15  // Chip select control pin
#define TFT_DC    2  // Data Command control pin
#define TFT_RST   4  // Reset pin (could connect to RST pin)
//#define TFT_RST  -1  // Set TFT_RST to -1 if display RESET is connected to ESP32 board RST

#define TOUCH_CS 5     // Chip select pin (T_CS) of touch screen
#define TOUCH_IRQ 35   // Interrupt pin (T_IRQ) from touch screen


#define LOAD_GLCD   // Font 1. Original Adafruit 8 pixel font needs ~1820 bytes in FLASH
#define LOAD_FONT2  // Font 2. Small 16 pixel high font, needs ~3534 bytes in FLASH, 96 characters
#define LOAD_FONT4  // Font 4. Medium 26 pixel high font, needs ~5848 bytes in FLASH, 96 characters
#define LOAD_FONT6  // Font 6. Large 48 pixel font, needs ~2666 bytes in FLASH, only characters 1234567890:-.apm
#define LOAD_FONT7  // Font 7. 7 segment 48 pixel font, needs ~2438 bytes in FLASH, only characters 1234567890:.
#define LOAD_FONT8  // Font 8. Large 75 pixel font needs ~3256 bytes in FLASH, only characters 1234567890:-.
#define LOAD_GFXFF  // FreeFonts. Include access to the 48 Adafruit_GFX free fonts FF1 to FF48 and custom fonts

#define SMOOTH_FONT


#define SPI_FREQUENCY  40000000

#define SPI_TOUCH_FREQUENCY  2500000

```
## Example
![alt text](https://github.com/arthur-dtrl/Weather-station/blob/main/images/Screen.png)
