#include "MultiSensorShield.h"

MultiSensor ms;

void setup(){
  Serial.begin(9600);
  ms.init();
}

void loop(){
  ms.loop(true);
  delay(100);
  
}

