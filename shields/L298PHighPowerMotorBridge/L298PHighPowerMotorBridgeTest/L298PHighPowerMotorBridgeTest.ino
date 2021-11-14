/** This is an example Program for the FunuMotor Shield with L298 Motor Driver
 *  
 *  GPL2 have fun ;) 
 *  Used Libs:    
 *  https://github.com/evert-arias/EasyBuzzer
 *  
 *  For german explanation visit 
 *  http://www.fambach.net
 */
#include"src/easybuzzer/EasyBuzzer.h"

#define BUZZER_PIN  4
#define PWM1_PIN    10
#define DIR1_PIN    12
#define PWM2_PIN    11
#define DIR2_PIN    13

unsigned int frequency = 400;
unsigned int duration = 1000;


/** play a test tone */
double testBuzzer() {
  // EasyBuzzer.beep(500, 1); // freq 1000, 10 times.
  EasyBuzzer.singleBeep(
    frequency,  // Frequency in hertz(HZ).
    duration   // Duration of the beep in milliseconds(ms).

  );
}

void setup() {

  // init serial
  Serial.begin(115200);

  // init motor pins
  pinMode( PWM1_PIN, OUTPUT);
  pinMode( DIR1_PIN, OUTPUT);
  pinMode( PWM2_PIN, OUTPUT);
  pinMode( DIR2_PIN, OUTPUT);

  // buzzer
  pinMode( BUZZER_PIN, OUTPUT);
  EasyBuzzer.setPin(BUZZER_PIN);

  Serial.println("Start Test");

}




void loop() {

  Serial.print( "Drive in first direction\t");
  // one direction
  digitalWrite(DIR1_PIN, HIGH);
  digitalWrite(DIR2_PIN, HIGH);
  for (int i = 0; i < 1024 ; i++) {
    EasyBuzzer.update();
    Serial.print(i % 10 == 0 ? "." : "");
    analogWrite(PWM1_PIN, i);
    analogWrite(PWM2_PIN, i);
    delay(100);

  }

  Serial.println( " STOP");
  // stop
  analogWrite(PWM1_PIN, 0);
  analogWrite(PWM2_PIN, 0);
  delay(1000);

  testBuzzer();


  Serial.print( "Drive in second direction\t");
  // the other direction
  digitalWrite(DIR1_PIN, LOW);
  digitalWrite(DIR2_PIN, LOW);

  for (int i = 0; i < 255 ; i++) {
    EasyBuzzer.update();
    Serial.print(i % 10 == 0 ? "." : "");
    analogWrite(PWM1_PIN, i);
    analogWrite(PWM2_PIN, i);
    delay(100);

  }

  // stop
  Serial.println( " STOP");
  analogWrite(PWM1_PIN, 0);
  analogWrite(PWM2_PIN, 0);
  delay(1000);
  testBuzzer();

  Serial.print( "Drive motor 1\t\t\t");
  digitalWrite(DIR1_PIN, HIGH);
  digitalWrite(DIR2_PIN, LOW);

  for (int i = 0; i < 255 ; i++) {
    EasyBuzzer.update();
    Serial.print(i % 10 == 0 ? "." : "");
    analogWrite(PWM1_PIN, i);
    // analogWrite(PWM2_PIN, i);
    delay(100);

  }

  // stop
  Serial.println( " STOP");
  analogWrite(PWM1_PIN, 0);
  analogWrite(PWM2_PIN, 0);
  delay(1000);

  testBuzzer();


  Serial.print( "Drive motor 2\t\t\t");
  digitalWrite(DIR1_PIN, LOW);
  digitalWrite(DIR2_PIN, HIGH);

  for (int i = 0; i < 255 ; i++) {
    EasyBuzzer.update();
    Serial.print(i % 10 == 0 ? "." : "");
    analogWrite(PWM1_PIN, i);
    analogWrite(PWM2_PIN, i);
    delay(100);

  }

  // stop
  Serial.println( " STOP");
  analogWrite(PWM1_PIN, 0);
  analogWrite(PWM2_PIN, 0);
  delay(1000);

  testBuzzer();
}
