
//*********************************************************/
#include "Telegram.h"
//*********************************************************/

// physics
const float ONE_ROUND_TICKS = 20;
const float WHEEL_DIAMETER = 34.52; // mmm
const float WHEEL_CIRCUMVERENCE  = WHEEL_DIAMETER * PI;
const float ONE_TICKS_SIZE = WHEEL_CIRCUMVERENCE / ONE_ROUND_TICKS;
const float AXIS_LENGTH = 133.91; // mm
const float TURN_CIRCUMVERENCE = 3.14 * AXIS_LENGTH; //(2 pi * r)
const float TICK_TURN = TURN_CIRCUMVERENCE / ONE_TICKS_SIZE;



//*********************************************************/
// odometerie
#define INT_PIN_LEFT 3
#define INT_PIN_RIGHT 2

int left = 0, right = 0;
boolean leftChanged = false, rightChanged = false;


void countLeft() {
  left ++;
  leftChanged = true;
}
void countRight() {
  right ++;
  rightChanged = true;
}


//*********************************************************/
//*********************************************************/
void setup() {
  Serial.begin(115200);

  //*********************************************************/


  //*********************************************************/
  attachInterrupt(digitalPinToInterrupt(INT_PIN_LEFT), countLeft, RISING);
  attachInterrupt(digitalPinToInterrupt(INT_PIN_RIGHT), countRight, RISING);

  //*********************************************************/


}

boolean changed ;
int sleft, sright;
void loop() {


  sleft = 0;
  sright = 0;
  changed = false;

  if (leftChanged) {
    sleft = left;
    left = 0;
    leftChanged = false;
    changed = true;
  }

  if (rightChanged) {
    sright = right;
    right = 0;
    rightChanged = false;
    changed = true;
  }
  if (changed) {
    Serial.println(Tele.sendPosTelegram(sleft, sright));
  }
  delay(1000);
}
