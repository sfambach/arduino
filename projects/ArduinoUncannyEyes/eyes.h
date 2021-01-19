/**
    I derived most of the code from adafruit uncanny eyes project.
    Put it into this class, let some things away and oh now only implement
    one display type i am so selfish ... if you need support for different
    displays, do not hasitate to change the code or contact me for help.

    This version of the uncanny eyes is from my point of view better understandable,
    but due to its structur less powerfull and less optimized as the original version.
    So if you have trouble with the performance or with memmory space consider to use the
    original version as basis.

    Author Stefan Fambach
    If you like visit my web page www.famnbach.net (only in german language)

   License MIT

   Origianl project info:

   https://github.com/adafruit/Uncanny_Eyes

   Adafruit invests time and resources providing this open source code,
   please support Adafruit and open-source hardware by purchasing products
   from Adafruit!


   Written by Phil Burgess / Paint Your Dragon for Adafruit Industries.
   MIT license.  SPI FIFO insight from Paul Stoffregen's ILI9341_t3 library.
   Inspired by David Boccabella's (Marcwolf) hybrid servo/OLED eye concept.

*/


#ifndef eyes__h
#define eyes__h

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <SPI.h>


// Enable ONE of these #includes -- HUGE graphics tables for various eyes:
#include "graphics/defaultEye.h"      // Standard human-ish hazel eye -OR-
//#include "graphics/dragonEye.h"     // Slit pupil fiery dragon/demon eye -OR-
//#include "graphics/noScleraEye.h"   // Large iris, no sclera -OR-
//#include "graphics/goatEye.h"       // Horizontal pupil goat/Krampus eye -OR-
//#include "graphics/newtEye.h"       // Eye of newt -OR-
//#include "graphics/terminatorEye.h" // Git to da choppah!
//#include "graphics/catEye.h"        // Cartoonish cat (flat "2D" colors)
//#include "graphics/owlEye.h"        // Minerva the owl (DISABLE TRACKING)
//#include "graphics/naugaEye.h"      // Nauga googly eye (DISABLE TRACKING)
//#include "graphics/doeEye.h"        // Cartoon deer eye (DISABLE TRACKING) 

class Eye  {

  private:

    static const uint8_t ease[];

#if defined(HERBERT)

#else
    static const uint32_t SPI_FREQ = 20000000;    // TFT: use max SPI
#endif
    int8_t _backLightPin;
    int8_t _lightSensorPin = -1;
    uint8_t _backLightMax = 255;
    uint32_t _startTime;
    SPISettings _settings; //(SPI_FREQ, MSBFIRST, SPI_MODE0);
    uint16_t _lightMin = 0;
    uint16_t _lightMax = 1023;

    boolean  _eyeInMotion      = false;
    int16_t  _eyeOldX = 512;
    int16_t  _eyeOldY = 512;
    int16_t  _eyeNewX = 512;
    int16_t  _eyeNewY = 512;
    uint32_t _eyeMoveStartTime = 0L;
    int32_t  _eyeMoveDuration  = 0L;
    int8_t _resetPin ;

#if defined(_ADAFRUIT_ST7735H_) || defined(_ADAFRUIT_ST77XXH_) // TFT
    Adafruit_ST7735 _display;
#endif



    //Iris *_iris;


  public:

    Eye( int8_t cs, int8_t dc, int8_t mosi, int8_t sclk, int8_t rst, int8_t backLightPin): 
      _display (cs, dc,  mosi, sclk, rst), _backLightPin(backLightPin),
      _settings(SPI_FREQ, MSBFIRST, SPI_MODE0),
      _resetPin(rst){
      
      
      _backLightMax = 255;
      //_iris = new Iris();

      ;

#if defined(_ADAFRUIT_ST7789H_) // 240x240 TFT
      _display.setAddrWindow(0, 0, 240, 240);
#elif defined(_ADAFRUIT_ST7735H_) || defined(_ADAFRUIT_ST77XXH_) // TFT
      _display.setAddrWindow(0, 0, 128, 128);
#else // OLED
      _display.writeCommand(SSD1351_CMD_SETROW);    // Y range
      _display.spiWrite(0);
      _display.spiWrite(SCREEN_HEIGHT - 1);
      _display.writeCommand(SSD1351_CMD_SETCOLUMN); // X range
      _display.spiWrite(0);
      _display.spiWrite(SCREEN_WIDTH  - 1);
      _display.writeCommand(SSD1351_CMD_WRITERAM);  // Begin write
#endif
    }



    void setup() {
      // init screen

      // switch backlight on
      pinMode(_backLightPin, OUTPUT);
      digitalWrite(_backLightPin, HIGH); // Backlight on

      reset();

      //initR(INITR_HALLOWING);        // Initialize HalloWing-oriented screen
      _display.initR(INITR_144GREENTAB);

      // optional comes later ;)
      //setRotation(eyeInfo[e].rotation);

      //      int x = width();
      //      int y = height();

      _display.fillScreen(0);
      delay(100);

      // display adafruit log (optional) comes later
      analogWrite(_backLightPin, _backLightMax);
      _startTime = millis();

      fadeInBacklight();

      
    }

    void loop() {
      //fadeInBacklight();
      //fadeOutBacklight();
    }

    void reset() {
      pinMode(_resetPin, OUTPUT);
      digitalWrite(_resetPin, LOW);  delay(1);
      digitalWrite(_resetPin, HIGH); delay(50);
      _display.fillScreen(ST77XX_BLACK);
    }


    void fadeInBacklight() {

      // analogWriteResolution(8); // only for other arduinos than uno
      for (int i = 0; i <= _backLightMax; i++) { // Fade logo in
        analogWrite(_backLightPin, i);
        delay(2);
      }
    }

    void fadeOutBacklight() {
      for (int i = _backLightMax; i >= 0; i--) {
        analogWrite(_backLightPin, i);
        delay(2);
      }
    }

    void draw() {




    }



}; // end class

const uint8_t Eye::ease[] = { // Ease in/out curve for eye movements 3*t^2-2*t^3
      0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  2,  2,  2,  3,   // T
      3,  3,  4,  4,  4,  5,  5,  6,  6,  7,  7,  8,  9,  9, 10, 10,   // h
      11, 12, 12, 13, 14, 15, 15, 16, 17, 18, 18, 19, 20, 21, 22, 23,   // x
      24, 25, 26, 27, 27, 28, 29, 30, 31, 33, 34, 35, 36, 37, 38, 39,   // 2
      40, 41, 42, 44, 45, 46, 47, 48, 50, 51, 52, 53, 54, 56, 57, 58,   // A
      60, 61, 62, 63, 65, 66, 67, 69, 70, 72, 73, 74, 76, 77, 78, 80,   // l
      81, 83, 84, 85, 87, 88, 90, 91, 93, 94, 96, 97, 98, 100, 101, 103, // e
      104, 106, 107, 109, 110, 112, 113, 115, 116, 118, 119, 121, 122, 124, 125, 127, // c
      128, 130, 131, 133, 134, 136, 137, 139, 140, 142, 143, 145, 146, 148, 149, 151, // J
      152, 154, 155, 157, 158, 159, 161, 162, 164, 165, 167, 168, 170, 171, 172, 174, // a
      175, 177, 178, 179, 181, 182, 183, 185, 186, 188, 189, 190, 192, 193, 194, 195, // c
      197, 198, 199, 201, 202, 203, 204, 205, 207, 208, 209, 210, 211, 213, 214, 215, // o
      216, 217, 218, 219, 220, 221, 222, 224, 225, 226, 227, 228, 228, 229, 230, 231, // b
      232, 233, 234, 235, 236, 237, 237, 238, 239, 240, 240, 241, 242, 243, 243, 244, // s
      245, 245, 246, 246, 247, 248, 248, 249, 249, 250, 250, 251, 251, 251, 252, 252, // o
      252, 253, 253, 253, 254, 254, 254, 254, 254, 255, 255, 255, 255, 255, 255, 255
    }; // n /from me too ;)



#endif
