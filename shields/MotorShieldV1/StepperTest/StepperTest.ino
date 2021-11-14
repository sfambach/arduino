// Adafruit Motor shield library
// copyright Adafruit Industries LLC, 2009
// this code is public domain, enjoy!

#include <AFMotor.h>

// Connect a stepper motor with 48 steps per revolution (7.5 degree)
// to motor port #2 (M3 and M4)
AF_Stepper motor(200, 1);

void setup() {
  Serial.begin(115200);           // set up Serial library at 9600 bps
  Serial.println("Stepper test!");

  motor.setSpeed(10);  // 10 rpm   
}

void loop() {
  Serial.println("Single coil steps");
  motor.step(200, FORWARD, SINGLE); 
  motor.step(200, BACKWARD, SINGLE); 

  Serial.println("Double coil steps");
  motor.step(200, FORWARD, DOUBLE); 
  motor.step(200, BACKWARD, DOUBLE);

  Serial.println("Interleave coil steps");
  motor.step(200, FORWARD, INTERLEAVE); 
  motor.step(200, BACKWARD, INTERLEAVE); 

  Serial.println("Micrsostep steps");
  motor.step(200, FORWARD, MICROSTEP); 
  motor.step(200, BACKWARD, MICROSTEP); 
}
