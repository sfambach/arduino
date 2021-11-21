
/***********************************************************/
#include <Servo.h>


/***********************************************************/
#include <Wire.h>
#include <Adafruit_MotorShield.h>

Adafruit_MotorShield AFMS; // = Adafruit_MotorShield();
// motors
Adafruit_DCMotor* motorLinks = AFMS.getMotor(1);
Adafruit_DCMotor* motorRechts = AFMS.getMotor(2);
// directions
//int dir[] = {FORWARD,BACKWARD,RELEASE};
//String textDir[] = {"FORWARD","BACKWARD","RELEASE"};

/***********************************************************/
// radio
#include <SPI.h>
#include "RF24.h"


RF24 radio(9, 10);              // define the object to control NRF24L01
byte addresses[][6] = {"007", "001"};
int data[9] = {512, 512, 0, 512, 512, 512, 1, 1, 1}; // define array used to save the communication data
int mode = 1;

/***********************************************************/

void setup() {
  Serial.begin(115200);

  Serial.println("init motor");
  AFMS.begin();
  motorLinks->setSpeed(0);
  motorRechts->setSpeed(0);
  motorLinks->run(BACKWARD);
  motorRechts->run(BACKWARD);


  Serial.println("init rf");
  radio.begin();                      // initialize RF24
  radio.setRetries(0, 15);            // set retries times
  radio.setPALevel(RF24_PA_LOW);      // set power
  radio.openWritingPipe(addresses[0]);
  radio.openReadingPipe(1, addresses[1]);
  radio.startListening();             // start monitoring

}

int shrink(int val){
  if(val>255) return 255;
  return val;
}

const int center = 512;
int leftOld = center;
int rightOld = center;
int leftSpeed = 0;
int rightSpeed = 0;
int span = 10;

void drive(int left, int right) {


  
  if (abs(leftOld - left) > span) {

    leftOld = left;

    if (left < 512) {
      leftSpeed = shrink((center-left) / 2);
      motorLinks->setSpeed(leftSpeed);
      motorLinks->run(BACKWARD);
    } else {
      leftSpeed = shrink((left - 512) / 2);
      motorLinks->setSpeed(leftSpeed);
      motorLinks->run(FORWARD);
    }

   
  }

  if (abs(rightOld - right) > span) {
    rightOld = right;

    if (right < 512) {
      rightSpeed = shrink((center-right) / 2);
      motorRechts->setSpeed(rightSpeed );
      motorRechts->run(BACKWARD);
    } else {
      rightSpeed = shrink((right - 512) / 2);
      motorRechts->setSpeed(rightSpeed);
      motorRechts->run(FORWARD);
    }

   
  } 


  
    Serial.print("left =");
    Serial.print(String(leftSpeed));
    Serial.print("right =");
    Serial.println(String(rightSpeed));
}
  void loop()
  {
    //    receiveData();
    if (mode == 1 || mode == 3) {
      radio.startListening();             // start monitoring
      receiveData();

//      for (int i = 0; i < 9; i++) {
//        Serial.print("(" + String(i) + ")");
//        Serial.print(data[i]);
//        Serial.print("; ");
//      }
//      Serial.println(".");

      drive(data[1], data[5]);

    }
  }



  void receiveData() {
    if ( radio.available()) {            // if receive the data
      while (radio.available()) {         // read all the data
        radio.read( data, sizeof(data) ); // read data
      }
      if (mode != data[2]) {
        // control the buzzer
        //tone(buzzerPin, 2000);
        //delay(500);
        //noTone(buzzerPin);
      }
      mode = data[2];

      // control the buzzer
      //      tone(buzzerPin, 2000);
      //      noTone(buzzerPin);
    }

  }

