/******************************************************************************
# Description
Test the Joystick input via 9 pin Sub D connector

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
#include"config.h"

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
// joystick
const uint8_t JOY_INPUTS [] ={JOY_UP, JOY_DOWN, JOY_LEFT, JOY_RIGHT, JOY_FIRE, JOY_PADDLEA,JOY_PADDLEB};
const String JOY_INPUTS_TEXT [] ={"UP","DOWN","LEFT","RIGHT","FIRE","PADDLE A", "PADDLE B"}; 
const uint8_t JOY_INPUT_COUNT = 5; //7 Dont use the paddles; 

void joy_setup(){
  for(int i =0; i < JOY_INPUT_COUNT; i++){
    pinMode(JOY_INPUTS[i],INPUT_PULLUP);
  }
}


void checkJoystick(){
  bool action = false;

  led_all(LOW);


  for(int i =0; i < JOY_INPUT_COUNT; i++){
    uint8_t state = digitalRead(JOY_INPUTS[i]);
    if(!state){
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
}


void loop() {
  checkJoystick();
  delay(100); // not needed but helpfull to don't spam the screen
}

// activate for serial event
/*void serialEvent(){
  DEBUG_PRINTLN("Serial Event");
}*/

/*****************************************************************************/
// Rest of implementations