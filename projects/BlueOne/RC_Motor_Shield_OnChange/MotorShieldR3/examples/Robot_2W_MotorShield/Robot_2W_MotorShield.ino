//Left Motor => Channel A
//Right Motor => Channel B

#include <MotorShieldR3.h>
MotorShieldR3 twoWheeled;
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
int velocitySlow = 100;

void setup() {

}

void loop() {  
  //twoWheeled.Forward_2W(leftWheelVelocity,rightWheelVelocity);
  twoWheeled.Forward_2W(velocityFast,velocityFast);
  delay(2000);
  twoWheeled.SetSpeeds_2W(velocitySlow,velocitySlow);
  delay(2000);
  twoWheeled.SetSpeedLeft_2W(velocityFast);
  delay(2000);
  twoWheeled.SetSpeedRight_2W(velocityFast);
  delay(2000);
  twoWheeled.Back_2W(velocityFast,velocityFast);  
  delay(2000); 
  twoWheeled.SetSpeeds_2W(velocitySlow,velocitySlow);
  delay(2000);
  twoWheeled.SetSpeedLeft_2W(velocityFast);
  delay(2000);
  twoWheeled.SetSpeedRight_2W(velocityFast);
  delay(2000);  
  twoWheeled.RotateLeft_2W(velocitySlow,velocitySlow); 
  delay(2000);  
  twoWheeled.RotateRight_2W(velocitySlow,velocitySlow);
  delay(2000);  
  twoWheeled.Stopped_2W();
  delay(2000);    
}
