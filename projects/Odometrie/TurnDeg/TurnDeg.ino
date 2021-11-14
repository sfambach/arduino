
//*********************************************************/
// motor
#include <Adafruit_MotorShield.h>
#include "ADFMotor2WD.h"
ADFMotor2WD drive(3,4);

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

int left=0,right=0;
int leftStop=0,rightStop=0;
boolean moving;
static int ONE_ROUND = 20;
const float ONE_ROUND_DISTANCE = 20.4; // cm
const float ONE_STEP_DISTANCE = ONE_ROUND_DISTANCE / ONE_ROUND; // cm

boolean changed = false;

void countLeft(){
  left ++;
  changed = true;
}
void countRight(){
  right ++;
  changed = true;
}

//*********************************************************/
// calibration 

  void calibrateMinSpeedSingle(TwoWireDrive::Side side){

      // init min speed 
//      DEBUG_PRINTLN("Set speed to 0");
//      drive.setSpeedMin(side, 0);
//
//      // drive to the next tik
//      DEBUG_PRINTLN("Set dir fw");
        drive.setDir(side,TwoWireDrive::Direction::BR);
//
//      DEBUG_PRINTLN("Set changed to false");
//      changed = false;
//      DEBUG_PRINTLN("Set speed 40");
//      drive.setSpeed(side, 50);
//
//      DEBUG_PRINTLN("wait until changed");
//      while(!changed){delay(1); };
//      DEBUG_PRINTLN("changed set speed to 0");
//      drive.setSpeed(side, 0);
    
      drive.setSpeedMin(side, 0);
      DEBUG_PRINTLN("Set changed to false");
      changed = false;
      drive.setDir(side,TwoWireDrive::Direction::FW);
      drive.setSpeedMin(side, 1);
     
      uint8_t speed = 0;
      while(!changed){
          drive.setSpeed(side, ++speed);
          DEBUG_PRINT(".");

          uint8_t count = 0;
          while(!changed && count < 100){
            delay(1);
            count ++;
          }
      }
      drive.setSpeedMin(side, speed);
      DEBUG_PRINT("Min Speed: ");
      DEBUG_PRINTLN(speed);
      drive.setSpeed(side, 0);
      drive.setDir(side,TwoWireDrive::Direction::BR);
  }

    void calibrate(){
         calibrateMinSpeedSingle(TwoWireDrive::Side::RIGHT);
         calibrateMinSpeedSingle(TwoWireDrive::Side::LEFT);
         
    }

    
//*********************************************************/
// Special movement

/** 
 *  turn around one wheel, one wheel drive the otherone stays still
 */
void whideTurnDeg(float deg){
 
    DEBUG_PRINT("Start Turn [DEG: ");
    DEBUG_PRINT(deg);
    if( deg == 0){
      return;
    }
    DEBUG_PRINT("][TC: ");
    DEBUG_PRINT(TURN_CIRCUMVERENCE);
    DEBUG_PRINT("][REL: ");
    DEBUG_PRINT(deg/360);
    // calculate distance 
    float dist = TURN_CIRCUMVERENCE * (deg/360);
    DEBUG_PRINT("][DIST: ");
    DEBUG_PRINT(dist);
    float ticks = dist / ONE_TICKS_SIZE;
    DEBUG_PRINT("][TICKS: ");
    DEBUG_PRINT(ticks);


    left  = 0;
    right = 0;

    if(deg > 0 ) {
       drive.setDir(TwoWireDrive::Side::LEFT, TwoWireDrive::Direction::FW);       
       drive.setDir(TwoWireDrive::Side::RIGHT, TwoWireDrive::Direction::BR);
       leftStop = ticks;
       
    }else {
       drive.setDir(TwoWireDrive::Side::LEFT, TwoWireDrive::Direction::BR);       
       drive.setDir(TwoWireDrive::Side::RIGHT, TwoWireDrive::Direction::FW);
       rightStop = ticks;
    }

    drive.setSpeedBoth(drive.getSpeedMin(TwoWireDrive::Side::LEFT)+10, drive.getSpeedMin(TwoWireDrive::Side::RIGHT)+10);

    

//    while(left < ticks){
//      delay(10);
//    }
//    drive.stop();

    DEBUG_PRINTLN("] End Turn");
}

/** 
 *  turn around the center of bot, one wheel drives forwart the other one drives backward.
 */
void turnDeg(float deg){
  
    DEBUG_PRINT("Start Turn [DEG: ");
    DEBUG_PRINT(deg);
    if( deg == 0){
      return;
    }
    DEBUG_PRINT("][TC: ");
    DEBUG_PRINT(TURN_CIRCUMVERENCE);
    DEBUG_PRINT("][REL: ");
    DEBUG_PRINT(deg/720);
    // calculate distance 
    float dist = TURN_CIRCUMVERENCE * (deg/720);
    DEBUG_PRINT("][DIST: ");
    DEBUG_PRINT(dist);
    float ticks = dist / ONE_TICKS_SIZE;
    DEBUG_PRINT("][TICKS: ");
    DEBUG_PRINT(ticks);


    left  = 0;
    right = 0;

    if(deg > 0 ) {
       drive.setDir(TwoWireDrive::Side::LEFT, TwoWireDrive::Direction::FW);       
       drive.setDir(TwoWireDrive::Side::RIGHT, TwoWireDrive::Direction::BW);
    }else {
       drive.setDir(TwoWireDrive::Side::LEFT, TwoWireDrive::Direction::BW);       
       drive.setDir(TwoWireDrive::Side::RIGHT, TwoWireDrive::Direction::FW);
    }

    leftStop = ticks;
    rightStop = ticks;
    drive.setSpeedBoth(drive.getSpeedMin(TwoWireDrive::Side::LEFT)+10, drive.getSpeedMin(TwoWireDrive::Side::RIGHT)+10);
    
//    while(left < ticks){
//      delay(10);
//    }
//    drive.stop();

    DEBUG_PRINTLN("] End Turn");
}

boolean isMoving(){
  
}

//*********************************************************/
void setup() {
  Serial.begin(115200); 
  Serial.println("2 WD DC Motor test!");
  
  //*********************************************************/

  
  //*********************************************************/
  attachInterrupt(digitalPinToInterrupt(INT_PIN_LEFT), countLeft, RISING);
  attachInterrupt(digitalPinToInterrupt(INT_PIN_RIGHT),countRight, RISING);

  //*********************************************************/
  drive.init();
  //drive.setDirBoth(TwoWireDrive::Direction::FW,TwoWireDrive::Direction::FW);

  calibrate();  
  turnDeg(90);
}

void loop() {
  uint8_t i;

 
  
  
//    Serial.print("left: ");
//    Serial.print(left);
//    Serial.print("[");
//    Serial.print(left * ONE_STEP_DISTANCE);
//    Serial.print(" cm]");
//    Serial.print(" right: ");
//    Serial.print(right);
//    Serial.print("[");
//    Serial.print(right * ONE_STEP_DISTANCE);
//    Serial.println(" cm]");

//  drive.setDir(TwoWireDrive::Side::LEFT, TwoWireDrive::Direction::BR);
//  Serial.println("LEFT Forward");
//  drive.setDir(TwoWireDrive::Side::LEFT, TwoWireDrive::Direction::FW);
//  for(int i = 0; i < 255; i++){
//        drive.setSpeed(TwoWireDrive::Side::LEFT,i);
//        delay(100);
//  }
//  delay(3000);
  
//  Serial.println("LEFT Backward ");
//  drive.setDir(TwoWireDrive::Side::LEFT, TwoWireDrive::Direction::BW);
//  for(int i = 0; i < 255; i++){
//        drive.setSpeed(TwoWireDrive::Side::LEFT,i);
//        delay(100);
//  }
//  delay(3000);
//
//  Serial.println("LEFT Stop");
//  drive.setDir(TwoWireDrive::Side::LEFT, TwoWireDrive::Direction::BR);
//  drive.stop();
//  delay(5000);
//
//
//  Serial.println("RIGHT Forward");
//  drive.setDir(TwoWireDrive::Side::RIGHT, TwoWireDrive::Direction::FW);
//  for(int i = 0; i < 50; i++){
//        drive.setSpeed(TwoWireDrive::Side::RIGHT,i);
//        delay(100);
//  }
//  delay(3000);
//  
//  Serial.println("RIGHT Backward ");
//  drive.setDir(TwoWireDrive::Side::RIGHT, TwoWireDrive::Direction::BW);
//  for(int i = 0; i < 50; i++){
//        drive.setSpeed(TwoWireDrive::Side::RIGHT,i);
//        delay(100);
//  }
//  delay(3000);
//
//  Serial.println("RIGHT Stop");
//  drive.setDir(TwoWireDrive::Side::RIGHT, TwoWireDrive::Direction::BR);
//  drive.stop();
//  delay(5000);
//
//
//   Serial.println("BOTH Forward");
//  drive.setDirBoth(TwoWireDrive::Direction::FW,TwoWireDrive::Direction::FW);
//  for(int i = 0; i < 50; i++){
//        drive.setSpeed(i,i);
//        delay(100);
//  }
//  delay(3000);
//  
//  Serial.println("BOTH Backward ");
//  drive.setDirBoth(TwoWireDrive::Direction::BW,TwoWireDrive::Direction::BW);
//  for(int i = 0; i < 50; i++){
//       drive.setSpeed(i,i);
//        delay(100);
//  }
//  delay(3000);
//
//  Serial.println("BOTH Stop");
//  drive.setDirBoth(TwoWireDrive::Direction::BR,TwoWireDrive::Direction::BR);
//  drive.stop();
//  delay(5000);
//

  
//
//  
//  //drive.setSpeed(75,75);
//  for(int8_t i = 0 ; i < 80; i+=10){
//
//     drive.setSpeed(i,i);
//
//     delay(500);
//  }
//  delay(1000);
//  Serial.print("Stop");
//  drive.stop();
//  delay(1000);
//
//  Serial.print("Backward");
//  for(int8_t i = 0 ; i > -80; i-=10){
//
//     drive.setSpeed(i,0);
//
//     delay(500);
//  }
//
//  
  
}
