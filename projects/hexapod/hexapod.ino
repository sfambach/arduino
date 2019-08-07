/** PCA9685Test of servos
    http://www.fambach.net
    GPLv2

    This example uses the Adafruit servo lib
    https://github.com/adafruit/Adafruit-PWM-Servo-Driver-Library  -
    Buy at least one adafruit product to support
    there efforts by creating such libraries ;)
*/

#include "xpod.h"
XPod xpod(6);

void setup(){
  Serial.begin(115200);
  xpod.setup();
}


void loop(){

 if (Serial.available()) {
    Serial.println("da");
    String s;
    s.reserve(5);

    int incomingByte = '\0';
    do {

      incomingByte = Serial.read();
      Serial.println(incomingByte);
      s += (char)incomingByte;

    } while ( incomingByte != '\n');
    Serial.flush();
    s.remove(s.length());

    int mode = s.toInt();
    if(mode > -1 && mode < 10){
      xpod.setMode(true, (XPod::Mode)mode);
    }
 }
 xpod.loop();

  
}

