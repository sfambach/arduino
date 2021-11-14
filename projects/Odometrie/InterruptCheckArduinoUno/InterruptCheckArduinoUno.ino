
#define INT_PIN_LEFT 2
#define INT_PIN_RIGHT 3

int left=0,right=0;
static int ONE_ROUND = 20;
const float ONE_ROUND_DISTANCE = 20.4; // cm
const float ONE_STEP_DISTANCE = ONE_ROUND_DISTANCE / ONE_ROUND; // cm

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
