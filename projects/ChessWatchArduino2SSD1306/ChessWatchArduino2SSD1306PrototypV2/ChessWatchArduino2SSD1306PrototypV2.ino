// Chess Watch step 1 test of the display
// www.fambach.net
// GPLv2
// this example was created with help of the examples delivered by Adafruit
// http://www.adafruit.com/category/63_98
// Buy at least one Adafruit product, and thank them for their good work ;)
/**************************************************************************/
#include "MemoryFree.h"
/**************************************************************************/
// SWITCHES
#define SW1 8 // switch one
#define SW2 9 // switch two
#define SW3 10 // switch three
#define SECONDS_FOR_RESET 3 // how long should the both switches be pressed to start a reset 

/***************************************************************************/
// OLED DISPLAY
#include <SPI.h>
#include <Wire.h>
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"

#define SCREEN_WIDTH 128 // width of the display
#define SCREEN_HEIGHT 64 // height of the display

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display1(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
Adafruit_SSD1306 display2(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, 4);

/***************************************************************************/
// watch
int half_height;
int half_width;
long millies_start;
int last_msec = 0;
long timer1 = 0;
long timer2 = 0;
bool stop = false;

const int START = 0;
const int T1 = 1;
const int T2 = 2;
int state = START;

void drawHousing(Adafruit_SSD1306 &displ) {
  // outer ring
  displ.drawCircle(half_width, half_height, half_height - 1, WHITE);

  // inner ring
  displ.drawCircle(half_width, half_height, 2, WHITE);

  //hour ticks
  for ( int z = 0; z < 360; z = z + 30 ) {
    //Begin at 0° and stop at 360°
    float angle = z ;
    angle = (angle / 57.29577951) ;
    int x2 = (half_width + (sin(angle) * 30));
    int y2 = (half_height - (cos(angle) * 30));
    int x3 = (half_width + (sin(angle) * (30 - 5)));
    int y3 = (half_height - (cos(angle) * (30 - 5)));
    displ.drawLine(x2, y2, x3, y3, WHITE);
  }
  displ.display();
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

    angle = (30+secs) * 6 ;
    if (angle != 0)angle = (angle / 57.29577951) ;
    x31 = (64 + (sin(angle) * (20 - 3)));
    y31 = (32 - (cos(angle) * (20 - 3)));
    disp.drawLine(half_width, half_height, x31, y31, WHITE);

    angle = (30+minutes) * 6 ;
    if (angle != 0) angle = (angle / 57.29577951) ;
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
  timer2 = 0;
  state = START;
  display1.clearDisplay();
  display2.clearDisplay();
  drawHousing(display1);
  drawHousing(display2);
  drawTime(timer1 , display1);
  delay(50);
  drawTime(timer2 , display2);
  delay(50);
}


void tooglePause() {
  stop = !stop;
}


void setup() {
  Serial.begin(9600);

  // buttons init
  pinMode(SW1, INPUT_PULLUP);
  pinMode(SW2, INPUT_PULLUP);
  pinMode(SW3, INPUT_PULLUP);
  Serial.print("Init display 1");
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display1.begin(SSD1306_SWITCHCAPVCC, 0x3D, false)) { // Address 0x3D for 128x64
    Serial.println(F("... SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  } else Serial.println("... OK");
  

  Serial.print("Init display 2");
  if (!display2.begin(SSD1306_SWITCHCAPVCC, 0x3C, false)) { // Address 0x3C for 128x64
    Serial.println(F("... SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  } else Serial.println("... OK");

  half_height  = display1.height() / 2;
  half_width = display1.width() / 2;
  resetTime();
}


void loop() {

  // i had some trouble with the switch
  if (!digitalRead(SW1) && digitalRead(SW2)) { // sw1 pressed but sw2 not
    Serial.println("SW 1 pressed");
    while (!digitalRead(SW1) && digitalRead(SW2));
    if (state == START) { // start own timer at start
      state = T2;
    } else {
      state = T1;
    }


    //millies_start = millis(); // reset millies counter

  } else if (digitalRead(SW1) && !digitalRead(SW2)) { // sw2 pressed but sw2 not
    Serial.println("SW 2 pressed");
    while (digitalRead(SW1) && !digitalRead(SW2));
    if (state == START) { // start own timer at start
      state = T1;
    } else {
      state = T2;
    }

    //millies_start = millis(); // reset millies counter

  } else if (!digitalRead(SW3)) {

    Serial.print("SW1+2 pressed .");
    // start timer for reset
    long mil = millis();
    while (!digitalRead(SW3)) {
    }

    if ( (millis() - mil) / 1000 > SECONDS_FOR_RESET) {
      resetTime();
      Serial.println(".. Reset ");

    } else {
      tooglePause();
    }
  }

  // count seconds
  if ((millis() - millies_start) > 1000) {
    millies_start += 1000;
    if (stop) {

    } else if (state == T1) {
      timer1++;
      drawTime(timer1, display1);
    } else if (state == T2) {
      timer2++;
      drawTime(timer2, display2);
    }
  }

  //delay(200);
}



