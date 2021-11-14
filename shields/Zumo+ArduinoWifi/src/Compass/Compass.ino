
#include "Engine.h"
#include "Credentials.h"

// get the engine driver
Engine engine(PWM_L,DIR_L,PWM_R,DIR_R);
uint8_t speed = 30;

void setup(){
  Serial.begin(115200);
  engine.init();
}



void loop(){

  
  //forward
  engine.setDirection(Engine::FOREWARD);
  engine.setSpeed(speed);
  delay(5000);
  
  //backward
  engine.setDirection(Engine::BACKWARD);
  delay(5000);
  
  // turn left
 
  engine.setDirection(Engine::LEFT, Engine::BACKWARD);
  engine.setDirection(Engine::RIGHT, Engine::FOREWARD);
  delay(5000);
  
  // turn right
  
  engine.setDirection(Engine::LEFT, Engine::FOREWARD);
  engine.setDirection(Engine::RIGHT, Engine::BACKWARD );
  delay(5000);
  
  // stop
  engine.setSpeed(0);
  delay(5000);
}
