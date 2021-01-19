#ifndef config_h
#define config_h

/**************************************************************************
  this is my new designed config file, 
  some parts of it are looking pretty the same like the old one 

  
  A lot of this project was taken from Adafruit uncanny eyes.
  They invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Here the link to the original Projekct
  https://github.com/adafruit/Uncanny_Eyes

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
*/
// port setup

#define TFT_CS        10 // Hallowing display control pins: chip select
#define TFT_RST       8  // Display reset
#define TFT_DC        9 // Display data/command select
#define TFT_BACKLIGHT  7 // Display backlight pin
#define TFT_MOSI 11  // Data out (SDA)
#define TFT_SCLK 13  // Clock out (SCL)

// #define SYNCPIN

#endif // config_h
