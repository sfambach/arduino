//Stepper
#include <AFMotor.h>


#define ANGLE 1.8 //1.8 // 360 degree / 200 steps
#define STEP_COUNT 200
#define CHECK_COUNT 4

#define PIN A2
uint8_t skipSteps = 20;
uint8_t stepDelay = 5;
uint8_t curStep = 0;

AF_Stepper motor(STEP_COUNT, 1);

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

  while ( curStep < skipSteps || ! digitalRead(PIN)){
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
    while (!digitalRead(PIN) || curStep < skipSteps) {
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

void setup() {
 Serial.begin(115200);
 
  // init end switch
 pinMode(PIN, INPUT);
 
 // init stepper
 initStepper();
 checkStepCount(CHECK_COUNT);
 delay(5000);
}

void loop() {
  // put your main code here, to run repeatedly:
  
 doSingleStep();

  if (digitalRead(PIN) && curStep > skipSteps) {
    Serial.println(curStep);
    curStep = 0;
  }

 

}
