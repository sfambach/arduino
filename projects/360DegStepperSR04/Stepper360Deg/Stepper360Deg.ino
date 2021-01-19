

/******************************************************************************************************/
// distance sensor 

//#define US100 // sonar sensor
//#define GY530 // laser sensor
#define FTMINI // laser sensor


/******************************************************************************************************/
//Stepper
#include <AFMotor.h>

#define STEP_COUNT 200
#define ANGLE 1.8 // 360 degree / 200 steps
#define CHECK_COUNT 4
#define ENDSTOP_PIN A2


AF_Stepper motor(STEP_COUNT, 1);

uint8_t curStep = 0;
uint8_t stepDelay = 5;
uint8_t skipSteps = 20;


void initStepper() {
  motor.setSpeed(100);  
  curStep = 0;
}

void doSingleStep(){
   curStep ++;
   motor.onestep(FORWARD, SINGLE);
   delay(stepDelay);
}

void goToEndstop(){

  curStep = 0;

  while ( curStep < skipSteps || ! digitalRead(ENDSTOP_PIN)){
    motor.onestep(FORWARD, SINGLE);  
    delay(stepDelay);
    curStep ++;
  }
  curStep = 0;
}

/** 
 *  check if the step counts are reliable
 *  @param checkCount set how much checks should be done
 */
void checkStepCount( uint8_t checkCount){

  if(checkCount < 1 ){
    Serial.print("check count must be bigger than 0 a good value is 4");
  }
  uint8_t checks[checkCount]; 
  uint8_t curCheck = 0;
  boolean checksOK = false;
  curStep = 0;
  
  while (!checksOK){
  
    // turn a round;
    Serial.print("Turn a round and count steps ... ");
    while (!digitalRead(ENDSTOP_PIN) || curStep < skipSteps) {
      doSingleStep();
    }
    checks[curCheck] = curStep;
    Serial.println(curStep);

    // check steps 
    for(int i = 0; i < checkCount; i++){

        // stop loop if the step counts  are not the same
        
        Serial.print(i);
        Serial.print(" : ");
        Serial.print(checks[i]);
        Serial.print(" == ");
        Serial.print(STEP_COUNT);
        Serial.print("? ");
        
        if(checks[i] != STEP_COUNT){
          Serial.println("NO");
          break;
        }
        Serial.println("Yes");

        // if all step counts are the same save result and go on
        if(i == checkCount-1){
          checksOK = true;
          Serial.println("Checks finished!");
        }
           
    }
    curCheck ++;
    // reset array counter if end of array was reached
    if(curCheck == checkCount){
      curCheck = 0;
    }
    curStep = 0;
  }
}

/******************************************************************************************************/
#if defined(GY530)
#include "Adafruit_VL53L0X.h"
Adafruit_VL53L0X sensor = Adafruit_VL53L0X();
void initDist() {
  Serial.println("Adafruit VL53L0X test");
  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while (1);
  }
}

long getDistMM() {
  VL53L0X_RangingMeasurementData_t measure;
  sensor.rangingTest(&measure, false); // pass in 'true' to get debug data printout!

  if (measure.RangeStatus != 4) {  // phase failures have incorrect data
    dist = measure.RangeMilliMeter;
  } else {
    dist = -1;
  }
  return dist;
}

/******************************************************************************************************/
#elif defined(FTMINI2)
#include "TFMini.h"
#include <SoftwareSerial.h>

// Setup software serial port 
SoftwareSerial mySerial(A1, A0);      // Uno RX (TFMINI TX), Uno TX (TFMINI RX)
TFMini tfmini;

void initDist() {
 // Step 2: Initialize the data rate for the SoftwareSerial port
  mySerial.begin(TFMINI_BAUDRATE);

  // Step 3: Initialize the TF Mini sensor
  tfmini.begin(&mySerial);
}

long getDistMM() {
  // get distance returns centimeter 
  uint16_t dist = tfmini.getDistance()*10;
  return dist;
}

/******************************************************************************************************/
#elif defined(FTMINI)
#include "TFmini.h"
#include <SoftwareSerial.h>

SoftwareSerial mySerial(A1, A0);
TFmini tfmini;

void initDist() {
  // init the sensor
  mySerial.begin(TFmini::DEFAULT_BAUDRATE);
  tfmini.attach(mySerial);
}

long getDistMM() {
  if (tfmini.available()) {
    return tfmini.getDistance();
    //            Serial.println(tfmini.getStrength());
    //            Serial.println(tfmini.getIntegrationTime());
  }
  return -1;
}
/******************************************************************************************************/
#else
// US100 Ultrasonic Distance Sensor
// time to distance conversion is
// divide by 2 (both ways to the obstical and back)
// divide by sonic constant 29.1
#define TRIGGER_PIN   A0
#define ECHO_PIN      A1
#define SC_MM         5.82
#define SC_CM         58.2

#define MAX_DUR       450 * 58.2 // ~6m in dur 
#define MIN_DUR       2 * 58.2 // ~2cm in dur
#define TO_SMALL      -1
#define TO_BIG        -2
#define INT_TO_SMALL  -3



/** get duration */
long getDur(int interval) {
  if (interval < 1) return -3;
  long dur = 0;

  for (int i = 0; i < interval; i++ ) {
    // init sensor
    noInterrupts();

    // start 10 us pulse
    digitalWrite(TRIGGER_PIN, HIGH);
    delayMicroseconds(50);
    digitalWrite(TRIGGER_PIN, LOW  );

    dur += pulseIn(ECHO_PIN, HIGH); //, 2* (MAX_DUR +1)); // determine the time
    interrupts();
  }

  dur /= interval;
  //Serial.print(dur);
  if (dur > MAX_DUR ) {
    return TO_BIG;
  }
  // else if (dur < MIN_DUR){ return TO_SMALL;}
  return dur;
}

void initDist() {
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

/** get the distance in milli meter*/
long getDistMM() {
  return (getDur(1) / SC_MM);
}

#endif
/******************************************************************************************************/



// Setup
String telegram;
void setup() {
  // seup serial
  Serial.begin(115200);
  Serial.println("Stepper test!");

  // init end switch
 // init end switch
 pinMode(ENDSTOP_PIN, INPUT);

  // init stepper 
 initStepper();
 checkStepCount(CHECK_COUNT);

  // init distance sensor
  initDist();

  telegram.reserve(40);
}

/******************************************************************************************************/



// loop
void loop() {

  //Serial.print("Current distance at ");
  float angle = curStep * ANGLE;

  long dur;
  long dist;

  dist = getDistMM();

  telegram = "[";
  telegram += angle ;
  telegram += ";";
  telegram += dist;
  telegram += ";]";

  Serial.println(telegram);

  //  Serial.print(" dist: ");
  //  if(dur > 0) Serial.println(dist);
  //  else if( dur == TO_BIG) Serial.println("TO FAR");
  //  else if( dur == TO_SMALL) Serial.println("TO NEAR");
  //
 
  doSingleStep();
  if (digitalRead(ENDSTOP_PIN) && curStep > skipSteps) {
    Serial.println(curStep);
    curStep = 0;
  }
}
