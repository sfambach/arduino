/**************************************************************************
  We changed adafruit uncanny eyes by packing the mains functionality in a class eyes
Currently only the TFT7735 display driver is supported.

  Currently Missing functionality:
  <li> Light Sensor </li>
  <li> More than one eye</li>
  <li> Support for different displays </li>  

  A lot of this project was taken from Adafruit uncanny eyes.
  They invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Here the link to the original Projekct
  https://github.com/adafruit/Uncanny_Eyes

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 **************************************************************************/

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <SPI.h>
#include "config.h"
#include "eyes.h"

Eye eye = Eye(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST, TFT_BACKLIGHT);

float p = 3.1415926;

//#include "eyes.h"

void setup(void) {
  Serial.begin(115200);
  Serial.print(F("Hello! ST77xx TFT Test"));

  randomSeed(analogRead(A3)); // Seed random() from floating analog input
  Serial.println(F("Initialized"));


    

  // large block of text
//  tft.fillScreen(ST77XX_BLACK);
    eye.setup();

 
}

void loop() {
 eye.loop();
}
