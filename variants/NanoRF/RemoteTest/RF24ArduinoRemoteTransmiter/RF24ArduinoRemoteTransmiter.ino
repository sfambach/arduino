// RF Sunfounder Remote with Nano and nRF24
// www.fambach.net
// GPL2
/*************************************************/
// RF
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

#define SWAP_X_Y    // swap x and y axis
#define SWAP_X      // swap x axis up and down 
#define SWAP_Y      // swap y axis up and down 



#define PIN_CE   9
#define PIN_CSN 10

RF24 radio(PIN_CE, PIN_CSN); // define the object to control NRF24L01
byte addresses[][6] = {"007", "001"};
int mode = 1;

#define SWITCH 0
#define X 1
#define Y 2
int data[3] = {0, 512, 512};

/*************************************************/
// Joystick
boolean pressed = false;
const byte PIN_BUTTON = 2;
const byte PIN_ANALOG_X = 1;
const byte PIN_ANALOG_Y = 0;
int analog_x = 512;
int analog_y = 512;

const int MIN_DELTA = 4; // minimum to detect changes

void setup() {
  Serial.begin(9600);

  /***********************************************************************/
  // init buttons
  pinMode(PIN_BUTTON, INPUT);

  /***********************************************************************/
  // init radio
  radio.begin();                      // initialize RF24
  radio.setRetries(0, 15);            // set retries times
  radio.setPALevel(RF24_PA_LOW);      // set power
  radio.openWritingPipe(addresses[1]);  // open delivery channel
  radio.openReadingPipe(1, addresses[0]);
  radio.stopListening();

}
bool change = false;
void loop() {

  // get button state

  boolean b = digitalRead(PIN_BUTTON);
  if (b != pressed) {
    pressed = b;
    change = true;

  }

  int cur = analogRead(PIN_ANALOG_X );
  int delta = analog_x - cur;

  if ( delta > MIN_DELTA || delta < -MIN_DELTA) {
    analog_x = cur;
    change = true;
  }

  cur = analogRead(PIN_ANALOG_Y );
  delta = analog_y - cur;

  if ( delta > MIN_DELTA || delta < -MIN_DELTA ) {
    analog_y = cur;
    change = true;
  }


  if (change) {
    data[SWITCH] = pressed;

#ifdef SWAP_X_Y
    data[Y] = analog_x;
    data[X] = analog_y;
#else
    data[X] = analog_x;
    data[Y] = analog_y;
#endif

#ifdef SWAP_X // swap up and down for x
    int deltaX = 512 - data[X];
    data[X] = 512 + deltaX;
#endif

#ifdef SWAP_Y // swap up and down for y
    int deltaY = 512 - data[Y];
    data[Y] = 512 + deltaY;
#endif

    Serial.print("Switch: ");
    Serial.print(data[SWITCH]);
    Serial.print(" X Axis:");
    Serial.print( data[X]);
    Serial.print(" Y Axis: ");
    Serial.println( data[Y]);

  }

  radio.write(data, sizeof(data));
}
