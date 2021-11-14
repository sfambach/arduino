/** This is an example Program for the FunuMotor Shield with L298 Motor Driver
 *  
 *  GPL2 have fun ;) 
 *  Used Libs:    
 *  https://github.com/evert-arias/EasyBuzzer
 *  
 *  For german explanation visit 
 *  http://www.fambach.net
 */
#include "L298PMotorBride.h"

L298PMotorBridge motor;

void setup() {

  // init serial
  Serial.begin(115200);
  Serial.println("Start Test");
  motor.init();
}




void loop() {

  Serial.print( "Drive in first direction\t");
  // one direction

  for (int i = -100; i < 100 ; i++) {
    Serial.print(i % 10 == 0 ? "." : "");
    motor.setSpeed(i,i);
    delay(100);
  }

  Serial.println( " STOP");
  motor.stop();
  delay(2000);
}
