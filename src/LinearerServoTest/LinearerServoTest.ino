// Linearare Servo Test 
// www.famnbach.net
// GPLv2
// -----------------------


#include <Servo.h>
#define SERVO_PIN 10
Servo myservo;


void setup() {
  Serial.begin(9600);
  pinMode(SERVO_PIN, OUTPUT);
  digitalWrite(SERVO_PIN, false);

  myservo.attach(SERVO_PIN);
  myservo.write(20);
}

void loop() {

  if (Serial.available()) {
    Serial.readString();
    myservo.write(140); // offen

    delay(4100);
    myservo.write(20); //Geschlossen
  }
}
