//Single motor control
#include <MotorShieldR3.h>
//Select channel with either 1 or 0
//Channel A => 1 => MotorShieldR3 single(1)
//Channel B => 0 => MotorShieldR3 single(0)
MotorShieldR3 single(1);
/*

  Default pins
  
  ------Channel A------
  pinDirA ....12 
  pinBrakeA...9 
  pinPwmA.....3
  
  ------Channel B------
  pinDirB.....13 
  pinBrakeB...8  
  pinPwmB.....11
  
*/

int velocityFast = 255;
int velocitySlow = 150;

void setup() {

}

void loop() {  
  //car.Forward_1W(SingleMotorVelocity);
  single.Forward_1W(velocitySlow);
  delay(2000);  
  single.SetSpeed_1W(velocityFast);
  delay(2000);  
  single.Back_1W(velocitySlow);  
  delay(2000);
  single.SetSpeed_1W(velocityFast);
  delay(2000);    
  single.Stopped_1W();
  delay(2000);    
}
