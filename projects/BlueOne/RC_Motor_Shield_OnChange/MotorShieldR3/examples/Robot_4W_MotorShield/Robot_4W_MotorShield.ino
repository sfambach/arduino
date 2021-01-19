//Front Motor (Steering) => Channel A
//Back Motor => Channel B

#include <MotorShieldR3.h>
MotorShieldR3 car;
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
  //car.Forward_4W(BackMotorVelocity);
  car.Forward_4W(velocitySlow);
  delay(2000);  
  car.SetSpeed_4W(velocityFast);
  delay(2000);  
  car.Back_4W(velocitySlow);  
  delay(2000);
  car.SetSpeed_4W(velocityFast);
  delay(2000);  
  car.Left_4W(); 
  delay(2000);  
  car.Right_4W();
  delay(2000);  
  car.ForwardLeft_4W(velocitySlow);
  delay(2000);
  car.ForwardRight_4W(velocitySlow);
  delay(2000);
  car.BackLeft_4W(velocitySlow);  
  delay(2000); 
  car.BackRight_4W(velocitySlow);  
  delay(2000);   
  car.Stopped_4W();
  delay(2000);    
}
