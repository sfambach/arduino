/******************************************************************************
# Description
Test the Joystick input via 9 pin Sub D connector

##Settings
see config .h

## Libs
Adafruit GFX https://github.com/adafruit/Adafruit_SSD1306
Adafruit 
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
#include"config.h"

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define FIRE 4

/*****************************************************************************/
// LED
uint8_t leds[] =  {LED_UP,LED_DOWN,LED_LEFT,LED_RIGHT,LED_FIRE};
const uint8_t LED_COUNT = 5;

void ledSelfTest(){
  // set all off 
  for(int i =0; i < LED_COUNT; i++){
    digitalWrite(leds[i],LOW);
  }


  for(int i =0; i < LED_COUNT; i++){
    digitalWrite(leds[i],HIGH);
    delay(LED_DEMO_DELAY);
    digitalWrite(leds[i],LOW);
  }
}

void led_all(bool state){
 for(int i =0; i < LED_COUNT; i++){
    digitalWrite(leds[i],state);
  }
}

// Init and loop
void led_setup(){ 
  // set all to input
  for(int i =0; i < LED_COUNT; i++){
    pinMode(leds[i],OUTPUT);
  }

}


/*****************************************************************************/
// display
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

  uint8_t width; 
  uint8_t height;

void display_drawBackground(){
  display.setRotation(2); // rotate screen by 180 deg

  // draw the frame

  display.drawRect(2, 2, width, height,SSD1306_WHITE );
  
  

  display.drawRect(display.width()/2-13, 4, 7, 7, SSD1306_WHITE);
  display.drawRect(display.width()/2-13, 13, 7, 7, SSD1306_WHITE);
  display.drawRect(display.width()/2-13, 22, 7, 7, SSD1306_WHITE);

  display.drawRect(display.width()/2-4, 4, 7, 7, SSD1306_WHITE);
  display.drawRect(display.width()/2-4, 13, 7, 7, SSD1306_WHITE);
  display.drawRect(display.width()/2-4, 22, 7, 7, SSD1306_WHITE);

  display.drawRect(display.width()/2+4, 4, 7, 7, SSD1306_WHITE);
  display.drawRect(display.width()/2+4, 13, 7, 7, SSD1306_WHITE);
  display.drawRect(display.width()/2+4, 22, 7, 7, SSD1306_WHITE);

  // left text
  display.setTextSize(1); 
  display.setTextColor(SSD1306_WHITE,SSD1306_BLACK); 
  display.setCursor(8,20); 
  display.println(F("Pad. A"));

  // right text
  display.setTextSize(1); 
  display.setTextColor(SSD1306_WHITE,SSD1306_BLACK); 
  display.setCursor(width/3*2+2,20); 
  display.println(F("Pad. B"));
  //display.draw

  display.display();
}

void displayDrawJoy(bool states[]){

  // first row 
  
  if( states[UP] && states[LEFT]){
    display.drawRect(display.width()/2-12, 5, 5, 5, SSD1306_WHITE);
  } else {
    display.drawRect(display.width()/2-12, 5, 5, 5, SSD1306_BLACK);
  } 
  
  if( states[UP] && !states[RIGHT] && !states[LEFT]){
    display.drawRect(display.width()/2-3, 5, 5, 5, SSD1306_WHITE);
    
  } else {
    display.drawRect(display.width()/2-3, 5, 5, 5, SSD1306_BLACK);
  }

  if( states[UP] && states[RIGHT]){
    display.drawRect(display.width()/2+5, 5, 5, 5, SSD1306_WHITE);
    
  } else {
    display.drawRect(display.width()/2+5, 5, 5, 5, SSD1306_BLACK);
  }
  
  // second row
  if( states[LEFT] && !states[UP] && !states[DOWN]){
    display.drawRect(display.width()/2-12, 14, 5, 5, SSD1306_WHITE);
  } else {
    display.drawRect(display.width()/2-12, 14, 5, 5, SSD1306_BLACK);
  } 
  
  if( states[FIRE]){
    display.drawRect(display.width()/2-3, 14, 5, 5, SSD1306_WHITE);
    
  } else {
    display.drawRect(display.width()/2-3, 14, 5, 5, SSD1306_BLACK);
  }

  if( states[RIGHT] && !states[UP] && !states[DOWN]){
    display.drawRect(display.width()/2+5, 14, 5, 5, SSD1306_WHITE);
    
  } else {
    display.drawRect(display.width()/2+5, 14, 5, 5, SSD1306_BLACK);
  }

// third row
  if( states[LEFT] && states[DOWN]){
    display.drawRect(display.width()/2-12, 23, 5, 5, SSD1306_WHITE);
  } else {
    display.drawRect(display.width()/2-12, 23, 5, 5, SSD1306_BLACK);
  } 
  
  if( states[DOWN] && !states[LEFT] && !states[RIGHT]){
    display.drawRect(display.width()/2-3, 23, 5, 5, SSD1306_WHITE);
    
  } else {
    display.drawRect(display.width()/2-3, 23, 5, 5, SSD1306_BLACK);
  }

  if( states[RIGHT] && states[DOWN]){
    display.drawRect(display.width()/2+5, 23, 5, 5, SSD1306_WHITE);
    
  } else {
    display.drawRect(display.width()/2+5, 23, 5, 5, SSD1306_BLACK);
  }

  // do the paddless

 

}


void display_drawBar(uint8_t x, uint8_t y, uint8_t width, uint8_t height, int value){
  
  // draw border 
  display.drawRect(x, y, width, height , SSD1306_WHITE);
  display.fillRect(x+1, y+1, width-2, height-2 , SSD1306_BLACK);
  

  int w2 = width /2;
  float step = ((float)width)/1024.0f;
 
  // fill the border
  if(value > 514 ){
    value -= 512;
    int curWidth = value * step;

#ifdef SHOW_BAR
    display.fillRect((x+width/2), y+1, curWidth, height-2 , SSD1306_WHITE);
#else
    display.drawLine(curWidth, y,curWidth , height+1 , SSD1306_WHITE);
#endif
  } if(value < 510 ){
    value = 512 - value;
    float curWidth = value * step;
   // 
#ifdef SHOW_BAR
   display.fillRect((x+width/2) - curWidth, y+1, curWidth, height-2 , SSD1306_WHITE);  
#else
  display.drawLine((x+width/2) - curWidth, y+1,(x+width/2) -curWidth , height+1 , SSD1306_WHITE);
#endif
  } else {
    display.drawLine(x+width/2, y+1,x+width/2 , height , SSD1306_WHITE);  
  }


}
void display_init(){
   if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  display.clearDisplay();

  display.display();
  delay(2000); // Pause for 2 seconds
  
   width = SCREEN_WIDTH-4;
   height = SCREEN_HEIGHT-4;

  display_drawBackground();
}
/*****************************************************************************/
// joystick
const uint8_t JOY_INPUTS [] ={JOY_UP, JOY_DOWN, JOY_LEFT, JOY_RIGHT, JOY_FIRE, JOY_PADDLEA,JOY_PADDLEB};
const String JOY_INPUTS_TEXT [] ={"UP","DOWN","LEFT","RIGHT","FIRE","PADDLE A", "PADDLE B"}; 
const uint8_t JOY_INPUT_COUNT = 5; //7 Dont use the paddles; 
bool JOY_state[]={false,false,false,false,false};

void joy_setup(){
  for(int i =0; i < JOY_INPUT_COUNT; i++){
    pinMode(JOY_INPUTS[i],INPUT_PULLUP);
  }

  pinMode(JOY_PADDLEA, INPUT);
  pinMode(JOY_PADDLEB, INPUT);
}


void checkJoystick(){
  bool action = false;

  led_all(LOW);


  for(int i =0; i < JOY_INPUT_COUNT; i++){
    uint8_t state = digitalRead(JOY_INPUTS[i]);
    JOY_state[i] = false;

    if(!state){
      JOY_state[i] = true;
      Serial.println(JOY_INPUTS_TEXT[i]);
      digitalWrite(leds[i],HIGH);
      action = false;
    } 
  }
}

/*****************************************************************************/
// Main Programm 

void setup() {
  Serial.begin(115200);
  DEBUG_PRINTLN("Setup");

  joy_setup();
  led_setup();

  ledSelfTest();

  display_init();
}


void loop() {
  checkJoystick();
  displayDrawJoy(JOY_state);

  int a = analogRead(JOY_PADDLEA);
  int b = analogRead(JOY_PADDLEB);


  display_drawBar(6, 4, width/3, height/3, a);
  display_drawBar(width/3*2-2, 4, width/3, height/3, b);

   display.display();
  delay(100); // not needed but helpfull to don't spam the screen
}

// activate for serial event
/*void serialEvent(){
  DEBUG_PRINTLN("Serial Event");
}*/

/*****************************************************************************/
// Rest of implementations