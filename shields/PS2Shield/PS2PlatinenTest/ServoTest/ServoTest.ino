/** Implemented by Stefan Fambach
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

void loop() {
    
  for (uint16_t curPulse = MIN_PULSE; pulselen < MAX_PULSE; curPulse++) {
    pwm.setPWM(servoPins[curServo], 0, curPulse);
    Serial.print(servoPins[curServo]);
    Serial.print(" : ");
    Serial.println(curPulse);
    delay(20);
  }

  delay(500);
  for (uint16_t curPulse = MAX_PULSE; pulselen > MIN_PULSE; curPulse--) {
    pwm.setPWM(servoPins[curServo], 0, curPulse);
    Serial.print(servoPins[curServo]);
    Serial.print(" : ");
    Serial.println(curPulse);
    
    delay(20);
    
  }

  delay(100);

  curServo ++;
  if (curServo > 3) curServo = 0;
}
