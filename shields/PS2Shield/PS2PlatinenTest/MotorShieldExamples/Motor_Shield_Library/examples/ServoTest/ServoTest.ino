
#include <Wire.h>
#include "Adafruit_MotorShield.h"
#include "Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 



void setServoPulse(uint8_t n, double pulse) {
  double pulselength;
  pulselength = 1000000;   // 1,000,000 us per second
  pulselength /= 50;   // 50 Hz
  Serial.print(pulselength); Serial.println(" us per period"); 
  pulselength /= 4096;  // 12 bits of resolution
  Serial.print(pulselength); Serial.println(" us per bit"); 
  pulse *= 1000;
  pulse /= pulselength;
  Serial.println(pulse);
  AFMS.setPWM(n, pulse);
}

void writeServo(uint8_t n,uint8_t angle){
  double pulse;
  pulse=0.5+angle/90.0;
  setServoPulse(n,pulse);
}

void setup(){
  Serial.begin(57600);
  AFMS.begin(50);  // create with the default frequency 1.6KHz
}

void loop() {
  writeServo(0,90);  
  writeServo(1,80); 
  writeServo(14,0); 
  writeServo(15,180); 
}