/** Implemented by Stefan Fambach
 *  V2 Enter Servo positin in degree between 0 and 180
 *  http://www.fambach.net
 *  Rewritten but based on the Adafruit examples 
 *  See also http://www.adafruit.com/products/815
  */
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>


// call the servo driver with the corretct address of the board.
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x60);

#define MIN_PULSE  150 
#define MAX_PULSE  480

#define MAX_DEG  180
#define MIN_DEG  0

#define NUM_SERVOS 4

#define SERVO_PIN_1 0
#define SERVO_PIN_2 1
#define SERVO_PIN_3 14
#define SERVO_PIN_4 15

uint8_t servoPins[] = {SERVO_PIN_1, SERVO_PIN_2,SERVO_PIN_3,SERVO_PIN_4};
uint8_t curServo = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("4 Servo Test");

  pwm.begin();
  pwm.setPWMFreq(50);  // 50hz is the standard

  delay(10);
}

int curDegMax = 180;
int curDegMin = 0;

void loop() {
    
  for (uint16_t curDeg = curDegMin; curDeg < curDegMax; curDeg++) {
    pwm.setPWM(servoPins[curServo], 0, map(curDeg, MIN_DEG , MAX_DEG,MIN_PULSE,MAX_PULSE ));
    Serial.print(servoPins[curServo]);
    Serial.print(" : ");
    Serial.println(curDeg);
    delay(20);
  }

  delay(500);
  for (uint16_t curDeg = curDegMax; curDeg > curDegMin ; curDeg--) {
    pwm.setPWM(servoPins[curServo], 0, map(curDeg, MIN_DEG , MAX_DEG,MIN_PULSE,MAX_PULSE ));
    Serial.print(servoPins[curServo]);
    Serial.print(" : ");
    Serial.println(curDeg);
    
    delay(20);
    
  }

  delay(100);

  curServo ++;
  if (curServo > 3) curServo = 0;
}
