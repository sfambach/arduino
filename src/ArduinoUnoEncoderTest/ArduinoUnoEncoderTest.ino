// Encoder Test for 1 Encoder
// www.fambach.net
// GPLv2
// Example derived from 
// http://andrewjkramer.net/motor-encoders-arduino/
//--------------------------------------

// pins for the encoder inputs
#define M1_ENCODER_1 3
#define M1_ENCODER_2 A2

// counters 
volatile unsigned long m1Count = 0;

void setup() {

  Serial.begin(9600);

  // setup all encoder pins
  pinMode(M1_ENCODER_1, INPUT);
  pinMode(M1_ENCODER_2, INPUT);
  
  // initialize hardware interrupts
  attachInterrupt(digitalPinToInterrupt(M1_ENCODER_1), m1EncoderEvent, CHANGE);
  
 
}

void loop() {
  Serial.print("Motor 1: ");
  Serial.println(m1Count);
  delay(500);
}

// encoder event for the interrupt call
void m1EncoderEvent() {
  if (digitalRead(M1_ENCODER_1) == HIGH) {
    if (digitalRead(M1_ENCODER_2) == LOW) {
      m1Count++;
    } else {
      m1Count--;
    }
  } else {
    if (digitalRead(M1_ENCODER_2) == LOW) {
      m1Count--;
    } else {
      m1Count++;
    }
  }
}


