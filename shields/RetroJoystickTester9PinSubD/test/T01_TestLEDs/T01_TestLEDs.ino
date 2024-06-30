/******************************************************************************
# Description
Test the LEDs of the Retro Joystick Tester

##Settings
#define LED_UP     11
#define LED_DOWN   8
#define LED_LEFT   9
#define LED_RIGHT 10 
#define LED_FIRE  12
#define DEMO_DELAY 500 // ms
#define DEMO_REPEAT_DELAY 200 // ms

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
// Define LED
#define LED_UP     11
#define LED_DOWN   8
#define LED_LEFT   9
#define LED_RIGHT 10 
#define LED_FIRE  12

uint8_t leds[] =  {LED_UP,LED_DOWN,LED_LEFT,LED_RIGHT,LED_FIRE};
const uint8_t LED_COUNT = 5;

/*****************************************************************************/
// LED Demo
#define DEMO_DELAY 500 // ms
#define DEMO_REPEAT_DELAY 2000 // ms 

void ledSelfTest(){

  // set all off 
  for(int i =0; i < LED_COUNT; i++){
    digitalWrite(leds[i],LOW);
  }


  for(int i =0; i < LED_COUNT; i++){
    digitalWrite(leds[i],HIGH);
    delay(DEMO_DELAY);
    digitalWrite(leds[i],LOW);
  }
}

/*****************************************************************************/
// Init and loop
void led_setup(){ 
  // set all to input
  for(int i =0; i < LED_COUNT; i++){
    pinMode(leds[i],OUTPUT);
  }

}

void led_loop(){
  ledSelfTest();
  delay(DEMO_REPEAT_DELAY);

}

/*****************************************************************************/
// Main Programm 

void setup() {
  Serial.begin(115200);
  DEBUG_PRINTLN("Setup");

  led_setup();
}


void loop() {
  led_loop();  
}

/*****************************************************************************/
// Rest of implementations