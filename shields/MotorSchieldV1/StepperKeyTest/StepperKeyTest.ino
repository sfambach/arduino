#include "OpenSmartUnoR3.h"
#include <AFMotor.h>
// 200 steps on M1/M2 connectors (2 = M3/ M4 Connector)
AF_Stepper motor(200, 1);
//OpenSmartUnoR3 board;
void setup() {

  // seup serial 
  Serial.begin(115200);
  Serial.println("Stepper test!");
  motor.setSpeed(100);  // 10 rpm   

  //board.init();
}

void loop() {
 // Serial.println("Single coil steps");
for(int i = 0; i < 255; i++){
 motor.onestep(FORWARD, SINGLE);
 delay(200);
}

for(int j = 255; j > 0; j--){
 motor.onestep(BACKWARD, INTERLEAVE);
}
//
//
//if(  board.getSwitch(OpenSmartUnoR3::SWITCH::SW2) ){
//  //Serial.println("SW2");
//  motor.onestep(FORWARD, DOUBLE);
//   //motor.step(1, FORWARD, SINGLE); 
//}else if(  board.getSwitch(OpenSmartUnoR3::SWITCH::SW1) )  {
// // Serial.println("SW1");
//   motor.onestep(BACKWARD, DOUBLE);
//   //motor.onestep(BACKWARD, MICROSTEP);
//   //motor.step(1, BACKWARD, SINGLE); 
//}else {
//  
//}
delay(100);
//  Serial.println("Double coil steps");
//  motor.step(100, FORWARD, DOUBLE); 
//  motor.step(100, BACKWARD, DOUBLE);
//
//  Serial.println("Interleave coil steps");
//  motor.step(100, FORWARD, INTERLEAVE); 
//  motor.step(100, BACKWARD, INTERLEAVE); 
//
//  Serial.println("Micrsostep steps");
//  motor.step(100, FORWARD, MICROSTEP); 
//  motor.step(100, BACKWARD, MICROSTEP); 
}
