/** PCA9685Test of servos
    http://www.fambach.net
    GPLv2

    This example uses the Adafruit servo lib
    https://github.com/adafruit/Adafruit-PWM-Servo-Driver-Library  -
    Buy at least one adafruit product to support
    there efforts by creating such libraries ;)
*/

// Servo things ...
#include "Adafruit_PWMServoDriver.h"
Adafruit_PWMServoDriver servodrv;
Adafruit_PWMServoDriver servodrv2();
#define SERVOMIN  100 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  580 // this is the 'maximum' pulse length count (out of 4096)
uint8_t servonum = 0;
uint8_t servoMax = 16;

void setup() {
  Serial.begin(115200);
  servodrv.begin();
  servodrv.setPWMFreq(60);
  delay(1000);

  for (int i = 0; i < servoMax ; i++) {
    servodrv.setPin(0, 340);
  }


  for (int i = 0; i < servoMax ; i++) {
    servodrv.setPin(0, 340);
  }
}


void setServoPulse(uint8_t n, double pulse) {
  double pulselength;

  pulselength = 1000000;   // 1,000,000 us per second
  pulselength /= 60;   // 60 Hz
  Serial.print(pulselength); Serial.println(" us per period");
  pulselength /= 4096;  // 12 bits of resolution
  Serial.print(pulselength); Serial.println(" us per bit");
  pulse *= 1000000;  // convert to us
  pulse /= pulselength;
  Serial.println(pulse);
  servodrv.setPWM(n, 0, pulse);
}

void loop() {

  // // Drive each servo one at a time
  //  Serial.println(servonum);
  //  for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++) {
  //    servodrv.setPWM(0, 0, pulselen);
  //    servodrv.setPWM(1, 0, pulselen);
  //  }
  //
  //  delay(500);
  //  for (uint16_t pulselen = SERVOMAX; pulselen > SERVOMIN; pulselen--) {
  //    servodrv.setPWM(0, 0, pulselen);
  //    servodrv.setPWM(1, 0, pulselen);
  //  }
  //
  //  delay(500);
  //
  //  servonum ++;


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
    int pos = map(s.toInt(), 0, 180, SERVOMIN, SERVOMAX);

    Serial.print("Got : ");
    Serial.println(pos);


    for (int i = 0; i < servoMax ; i++) {
      servodrv.setPin(i, pos);

    }

  }
}

