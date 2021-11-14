#include <Adafruit_MotorShield.h>

#include "ADFMotor2WD.h"

ADFMotor2WD drive(3,4);

void setup() {
  Serial.begin(115200); 
  Serial.println("2 WD DC Motor test!");
  drive.init();
}

void loop() {
  uint8_t i;

  Serial.println("LEFT Forward");
  drive.setDir(TwoWireDrive::Side::LEFT, TwoWireDrive::Direction::FW);
  for(int i = 0; i < 100; i++){
        drive.setSpeed(TwoWireDrive::Side::LEFT,i);
        delay(100);
  }
  delay(3000);
  
  Serial.println("LEFT Backward ");
  drive.setDir(TwoWireDrive::Side::LEFT, TwoWireDrive::Direction::BW);
  for(int i = 0; i < 100; i++){
        drive.setSpeed(TwoWireDrive::Side::LEFT,i);
        delay(100);
  }
  delay(3000);

  Serial.println("LEFT Stop");
  drive.setDir(TwoWireDrive::Side::LEFT, TwoWireDrive::Direction::BR);
  drive.stop();
  delay(5000);


  Serial.println("RIGHT Forward");
  drive.setDir(TwoWireDrive::Side::RIGHT, TwoWireDrive::Direction::FW);
  for(int i = 0; i < 100; i++){
        drive.setSpeed(TwoWireDrive::Side::RIGHT,i);
        delay(100);
  }
  delay(3000);
  
  Serial.println("RIGHT Backward ");
  drive.setDir(TwoWireDrive::Side::RIGHT, TwoWireDrive::Direction::BW);
  for(int i = 0; i < 100; i++){
        drive.setSpeed(TwoWireDrive::Side::RIGHT,i);
        delay(100);
  }
  delay(3000);

  Serial.println("RIGHT Stop");
  drive.setDir(TwoWireDrive::Side::RIGHT, TwoWireDrive::Direction::BR);
  drive.stop();
  delay(5000);


   Serial.println("BOTH Forward");
  drive.setDirBoth(TwoWireDrive::Direction::FW,TwoWireDrive::Direction::FW);
  for(int i = 0; i < 100; i++){
        drive.setSpeed(i,i);
        delay(100);
  }
  delay(3000);
  
  Serial.println("BOTH Backward ");
  drive.setDirBoth(TwoWireDrive::Direction::BW,TwoWireDrive::Direction::BW);
  for(int i = 0; i < 100; i++){
       drive.setSpeed(i,i);
        delay(100);
  }
  delay(3000);

  Serial.println("BOTH Stop");
  drive.setDirBoth(TwoWireDrive::Direction::BR,TwoWireDrive::Direction::BR);
  drive.stop();
  delay(5000);


  
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
