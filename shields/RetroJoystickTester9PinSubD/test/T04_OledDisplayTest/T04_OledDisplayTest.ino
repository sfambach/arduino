/******************************************************************************
# Description
Retro Joystick Tester, test the display
##Settings

## Credits 
* Licence: AGPL3
* Author:  S. Fambach
Visit http://www.fambach.net if you want
******************************************************************************/


/*****************************************************************************/
// Debuging

#define DEBUG
#ifdef DEBUG
#define DEBUG_PRINTLN(x) Serial.println(x)
#define DEBUG_PRINT(x) Serial.print(x)
#else
#define DEBUG_PRINTLN(x)
#define DEBUG_PRINT(x)
#endif

/*****************************************************************************/
// Screen
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 34 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

/*****************************************************************************/
// XXXXXXXX

/*****************************************************************************/
// XXXXXXXX

/*****************************************************************************/
// XXXXXXXX

/*****************************************************************************/
// XXXXXXXX
void drawBackground(){
   
  // draw the frame
  uint8_t width = display.width()-4;
  uint8_t height = display.height()-4;
  display.drawRect(2, 2, width, height, SSD1306_WHITE);
  
  display.fillRect(4, 4, width/3, height-4, SSD1306_WHITE);
  display.fillRect(width/3*2, 4, width/3, height-4, SSD1306_WHITE);
  

display.fillRect(display.width()/2-13, 4, 7, 7, SSD1306_WHITE);
display.fillRect(display.width()/2-13, 13, 7, 7, SSD1306_WHITE);
display.fillRect(display.width()/2-13, 22, 7, 7, SSD1306_WHITE);

display.fillRect(display.width()/2-4, 4, 7, 7, SSD1306_WHITE);
display.fillRect(display.width()/2-4, 13, 7, 7, SSD1306_WHITE);
display.fillRect(display.width()/2-4, 22, 7, 7, SSD1306_WHITE);

display.fillRect(display.width()/2+4, 4, 7, 7, SSD1306_WHITE);
display.fillRect(display.width()/2+4, 13, 7, 7, SSD1306_WHITE);
display.fillRect(display.width()/2+4, 22, 7, 7, SSD1306_WHITE);


  display.display();
}


/*****************************************************************************/
// Main Programm 

void setup() {
  Serial.begin(115200);
  DEBUG_PRINTLN("Setup");

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

display.clearDisplay();

  display.display();
  delay(2000); // Pause for 2 seconds
  

  drawBackground();
}


void loop() {
  //DEBUG_PRINTLN("Main Loop");
}

// activate for serial event
/*void serialEvent(){
  DEBUG_PRINTLN("Serial Event");
}*/

/*****************************************************************************/
// Rest of implementations