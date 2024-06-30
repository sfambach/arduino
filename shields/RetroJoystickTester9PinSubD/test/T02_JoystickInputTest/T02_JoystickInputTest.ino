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

/*****************************************************************************/
// Defines

#define JOY_UP      4
#define JOY_DOWN    5
#define JOY_LEFT    6
#define JOY_RIGHT   7
#define JOY_FIRE    3
#define JOY_PADDLEA A0
#define JOY_PADDLEB A1

const uint8_t JOY_INPUTS [] ={JOY_UP, JOY_DOWN, JOY_LEFT, JOY_RIGHT, JOY_FIRE, JOY_PADDLEA,JOY_PADDLEB};
const String JOY_INPUTS_TEXT [] ={"UP","DOWN","LEFT","RIGHT","FIRE","PADDLE A", "PADDLE B"}; 
const uint8_t JOY_INPUT_COUNT = 5; //7 Dont use the paddles; 

/*****************************************************************************/
// setup joystick pins
void joy_setup(){
  for(int i =0; i < JOY_INPUT_COUNT; i++){
    pinMode(JOY_INPUTS[i],INPUT_PULLUP);
  }
}

/*****************************************************************************/
// Check inputs

void checkJoystick(){
  bool action = false;
  for(int i =0; i < JOY_INPUT_COUNT; i++){
    uint8_t state = digitalRead(JOY_INPUTS[i]);
    if(!state){
      Serial.println(JOY_INPUTS_TEXT[i]);
      action = false;
    }
  }
}

/*****************************************************************************/
// XXXXXXXX

/*****************************************************************************/
// XXXXXXXX


/*****************************************************************************/
// Main Programm 

void setup() {
  Serial.begin(115200);
  DEBUG_PRINTLN("Setup");

  joy_setup();
}


void loop() {
  checkJoystick();
  delay(100);
}

// activate for serial event
/*void serialEvent(){
  DEBUG_PRINTLN("Serial Event");
}*/

/*****************************************************************************/
// Rest of implementations