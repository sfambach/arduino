// Chess Watch step 1 test of the display
// www.fambach.net
// GPLv2
// this example was created with help of the examples delivered by Adafruit
// http://www.adafruit.com/category/63_98
// Buy at least one Adafruit product, and thank them for their good work ;)
/**************************************************************************/
/**************************************************************************/
// SWITCHES
#define RESET1 8 // reset switch one


/***************************************************************************/
// OLED DISPLAY
#include <SPI.h>
#include <Wire.h>
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"

#define SCREEN_WIDTH 128 // width of the display
#define SCREEN_HEIGHT 64 // height of the display

#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display1(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

/***************************************************************************/
// watch
int half_height;
int half_width;
long millies_start;
int last_msec = 0;
long timer1 = 0;


void drawHousing(Adafruit_SSD1306 &displ) {
  // outer ring
  display1.drawCircle(half_width, half_height, half_height - 1, WHITE);

  // inner ring
  display1.drawCircle(half_width, half_height, 2, WHITE);

  //hour ticks
  for ( int z = 0; z < 360; z = z + 30 ) {
    //Begin at 0° and stop at 360°
    float angle = z ;
    angle = (angle / 57.29577951) ;
    int x2 = (half_width + (sin(angle) * 30));
    int y2 = (half_height - (cos(angle) * 30));
    int x3 = (half_width + (sin(angle) * (30 - 5)));
    int y3 = (half_height - (cos(angle) * (30 - 5)));
    display1.drawLine(x2, y2, x3, y3, WHITE);
  }
  display1.display();
}

int lastSecs = 0;
void drawTime(int seconds , Adafruit_SSD1306 &disp) {



  int minutes = 0;
  int secs = seconds;
  if (seconds > 60) {
    minutes = seconds / 60;
    secs = seconds % 60;
  }

  float angle = 0.0f;
  int x31 = 0;
  int y31 = 0;
  if (seconds != lastSecs) {
    lastSecs = seconds;
    disp.clearDisplay();
    drawHousing(disp);

    //    // delete old seconds
    //    angle = last_secs * 6 ;
    //    angle = (angle / 57.29577951) ;
    //    x31 = (64 + (sin(angle) * (20 - 3)));
    //    y31 = (32 - (cos(angle) * (20 - 3)));
    //    disp.drawLine(half_width, half_height, x31, y31, BLACK);
    //
    //    // delte old minutes
    //    angle = last_mins * 6 ;
    //    angle = (angle / 57.29577951) ;
    //    x31 = (64 + (sin(angle) * (20 - 3)));
    //    y31 = (32 - (cos(angle) * (20 - 3)));
    //    disp.drawLine(half_width, half_height, x31, y31, BLACK);


    angle = secs * 6 ;
    angle = (angle / 57.29577951) ;
    x31 = (64 + (sin(angle) * (20 - 3)));
    y31 = (32 - (cos(angle) * (20 - 3)));
    disp.drawLine(half_width, half_height, x31, y31, WHITE);

    angle = minutes * 6 ;
    angle = (angle / 57.29577951) ;
    x31 = (64 + (sin(angle) * (20 - 3)));
    y31 = (32 - (cos(angle) * (20 - 3)));
    disp.drawLine(half_width, half_height, x31, y31, WHITE);

    disp.display();
  }

  Serial.print(minutes);
  Serial.print(":");
  Serial.println(seconds);
}


void resetTime() {
  millies_start = millis();
  timer1 = 0;
  display1.clearDisplay();
  drawHousing(display1);
  drawTime(timer1 , display1);
}


void setup() {
  Serial.begin(9600);

  // buttons init
  pinMode(RESET1, INPUT_PULLUP);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display1.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }

  half_height  = display1.height() / 2;
  half_width = display1.width() / 2;
  resetTime();
}

long seconds = 0;

void loop() {

  // i had some trouble with the switch
  if (!digitalRead(RESET1)) { // stupid but better than pinmode input and == 1
    resetTime();
    Serial.println("Reset 1 pressed");
  }


  // count seconds
  if ((millis() - millies_start) > 1000) {
    millies_start += 1000;
    timer1++;
    drawTime(timer1, display1);
  }

  delay(200);
}


