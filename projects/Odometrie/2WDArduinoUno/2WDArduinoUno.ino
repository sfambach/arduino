
#define INT_PIN_LEFT 2
#define INT_PIN_RIGHT 3

 

/**
 * measure distance from mid of wheel 1 to mid of wheel 2. 
 * Or measure from outer edge of both wheels and substract the width of one wheel. (16 -2.5 in my case) 
 */
#define DISTNACE_BETWEEN_WHEELS 13.5 //cm 

int left=0,right=0;

/** 
 *  tick of your odometrie for one round of a wheel
 */
static int ONE_ROUND = 20;

/** 
 *  Draw a line on down position of the wheel and a line on the underground. 
 *  Now dive your robot forward until the line is on down position again.
 *  Now mark this position and measure the distance.
 */
const float ONE_ROUND_DISTANCE = 20.4; // cm

/** 
 *  distance of one tick
 */
const float ONE_STEP_DISTANCE = ONE_ROUND_DISTANCE / ONE_ROUND; // cm


/** 
 *  Only for indication on console
 */
boolean changed = false;

void countLeft(){
  left ++;
  changed = true;
}
void countRight(){
  right ++;
  changed = true;
}


void setup() {
  Serial.begin(115200);
  attachInterrupt(digitalPinToInterrupt(INT_PIN_LEFT), countLeft, RISING);
  attachInterrupt(digitalPinToInterrupt(INT_PIN_RIGHT),countRight, RISING);

}

void loop() {


  if(changed){
    changed = false;
    Serial.print("left: ");
    Serial.print(left);
    Serial.print("[");
    Serial.print(left * ONE_STEP_DISTANCE);
    Serial.print(" cm]");
    Serial.print(" right: ");
    Serial.print(right);
    Serial.print("[");
    Serial.print(right * ONE_STEP_DISTANCE);
    Serial.println(" cm]");
  }

}
