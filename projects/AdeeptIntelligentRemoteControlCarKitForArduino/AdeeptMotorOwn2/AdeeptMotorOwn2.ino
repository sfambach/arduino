
/***********************************************************/
#include <Servo.h>


/***********************************************************/
#include <Wire.h>
#include <Adafruit_MotorShield.h>

Adafruit_MotorShield AFMS; // = Adafruit_MotorShield();
// motors
Adafruit_DCMotor* motorLinks = AFMS.getMotor(1);
Adafruit_DCMotor* motorRechts = AFMS.getMotor(2);

int center1 = -1;
int center2 = -1;
int speedOld = -1;
int dirOld = -1;

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


   
      center1 = 512; //data[1];
      speedOld  = 512; // data[1];
   

   
      center2 = 512; //  data[0];
      dirOld= 512; //  data[0];
   

  Serial.println("init rf");
  radio.begin();                      // initialize RF24
  radio.setRetries(0, 15);            // set retries times
  radio.setPALevel(RF24_PA_LOW);      // set power
  radio.openWritingPipe(addresses[0]);
  radio.openReadingPipe(1, addresses[1]);
  radio.startListening();             // start monitoring

}

int shrink(int val) {
  if (val > 199) return 199;
  return val;
}


int span = 10;
int dir = BACKWARD;
int delta1 = 0;
int delta2 = 0;
int curSpeed = 0;

void drive(int speed, int dir) {

  

 
    dirOld = dir;

    // do some calculation for the steering
    // value 0 to 1024 center is ~512
    if (dir > center2) { // left

      // get a value between 0 and 255/5
      // substract the dir from center 2 to get a value between 0 and 512
      // divide by 2 to get a value between 0 and 255
      // divide by 5 to get 1/5 of value, higher values are possible but makes the steering difficult
      int val =  shrink((center2 - dir) / 2) / 5;
      delta1 = val;
      delta2 = -val;
      
    } else { // right

      // get a value between 0 and 255/5
      // substract center2 to get a value under 512, divide by 2 to get a value betwee 0 and 256 
      // divide by 5 to get 1/5 of value, higher values are possible but makes the steering difficult
      int val =  shrink((dir - center2) / 2) / 5;
      delta1 = -val;
      delta2 = val;
    }

 

    // do some speed calculation, shrink() shrinks the max value to a value that makes max seep + steering smaller 255
    if (speed < center1) {
      curSpeed = shrink((center1 - speed) / 2);
      dir  = BACKWARD;
    } else {
      curSpeed = shrink((speed - center1) / 2 );
      dir  = FORWARD;
    }
  
  motorLinks->run(dir);
  motorRechts->run(dir);
  motorLinks->setSpeed(curSpeed + delta1);
  motorRechts->setSpeed(curSpeed + delta2);


  Serial.print("left =");
  Serial.print(String(curSpeed));
  Serial.print("delta =");
  Serial.println(String(delta1));
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

    drive(data[1], data[0]);

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

