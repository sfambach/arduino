/******************************************************************************
# Neo Pixel Roulette 
This programm simulates a roulette, or better the ball of a roulette
with help of a neo pixel ring. 

##Settings
SIGNAL_PIN - pin for one wire neo pixel control
LED_COUNT - Quantity of LEDs
BRIGHTNESS - Brightness of all leds
ONCE - Spin once, reset needed to spin again, document out to switch off
NEW_START_DELAY - delay in ms to start again, only if ONCE is not declared
RANDOM_START_LED - if defined on of led count is selected to start. 
START_SPEED - The speed of the ball whenn its thown into the Roulette this is only a value of ms to start with good value is 10 ms;
FRICTION - value in ms added to start speed to slow down 
STOP_BALL - define when a ball stands still, value in ms if delay_cur in ms  > STOP_BALL then stop this round

## Calculation basis 
Simply add somthing to the delay until it breaches a defined shrink


## Libs
Adafruit Neo Pixel Lib https://github.com/adafruit/Adafruit_NeoPixel

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
// Neo Pixel setup
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define SIGNAL_PIN 7 // pin for data 
#define LED_COUNT 16 

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_COUNT, SIGNAL_PIN, NEO_GRB + NEO_KHZ800);

#define BLACK 0x000000
#define WHITE 0xFFFFFF
#define RED   0xFF0000
#define GREEN 0x00FF00

/*****************************************************************************/
// Settings for the Roulette

// #define ONCE 
#define RANDOM_START_LED
#define BRIGHTNESS 50
#define NEW_START_DELAY 1000 // ms
#define START_SPEED 10 // ms
#define FRICTION 1 //ms
#define STOP_BALL 500 // ms
#define DELAY_NEW_ROUND 4000 // ms

#define COLOR_0 GREEN;
#define COLOR_1 RED; 
#define COLOR_2 WHITE;


/*****************************************************************************/
// XXXXXXXX

/*****************************************************************************/
// XXXXXXXX

/*****************************************************************************/
// XXXXXXXX


/*****************************************************************************/
// Main Programm 

void setup() {
  Serial.begin(115200);
  DEBUG_PRINTLN("Setup");

  // init random number generator
  randomSeed(analogRead(0));
  
  // init led stripe
  strip.setBrightness(BRIGHTNESS);
  strip.begin();
  strip.setBrightness(50);
  strip.show(); // Initialize all pixels to 'off'
}


void loop() {

  throwBall();

#ifdef ONCE
  while(1);
#else 
  delay(DELAY_NEW_ROUND);
#endif 
}

uint16_t last_index = -1; // led that was on
void throwBall(){
  
  uint32_t color_cur = BLACK;
  uint16_t led_index = 0;
  
  float delay_cur = START_SPEED;
  long friction_cur = FRICTION;
  bool run = true;

  long time_start = millis();

  // determine start led if RANDOM_START_LED is defined
  
  #ifdef RANDOM_START_LED
  led_index = random(0,strip.numPixels());
  #endif 


  while(run){
  
    // determine color 
    if(led_index == 0){ // zero color, often green
      color_cur = COLOR_0;
    } else if ( (led_index % 2) == 0  ) { // even index led color
      color_cur = COLOR_1;
        
    } else { // uneven color
      color_cur = COLOR_2;
    }

    // set new led 
    strip.setPixelColor(led_index, color_cur);

    // erase old led 
    strip.setPixelColor(last_index, BLACK);

    // refresh pixel ring
    strip.show();

    // save current index to delete it next round
    last_index = led_index; 

    // select next led
    led_index ++;

    // if end of the ring is reached start at the first led
    if(led_index >= strip.numPixels()){
      led_index = 0;
    }

    // calculate delay
    delay_cur = getDelayBySpeedCalculation()
    if(delay_cur > STOP_BALL){
      run = false;
    } else {
      delay(delay_cur);
    }
  }

}

 long getDelayBySpeedCalculation(long time_cur){

    // formula s = Vs * tp + 0.5 *  a * tp²
    float speed = speed_start * 

 }


