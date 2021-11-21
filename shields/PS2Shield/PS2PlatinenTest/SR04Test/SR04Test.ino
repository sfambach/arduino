// *************************************************
// SR04 Ultrasonic Distance Sensor
// time to distance conversion is
// divide by 2 (both ways to the obstical and back)
// divide by sonic constant 29.1
#define TRIGGER_PIN   8
#define ECHO_PIN      7
#define SC_CM         58.2

#define MAX_DUR       164600 // ~3m in dur 
#define MIN_DUR       116 // ~2cm in dur
#define TO_SMALL      -1
#define TO_BIG        -2
#define INT_TO_SMALL  -3


/** get duration */
long getDur(int interval) {
  if (interval < 1) return -3;
  long dur = 0;

  for (int i = 0; i < interval; i++ ) {
    // init sensor
    digitalWrite(TRIGGER_PIN, LOW);
    delayMicroseconds(3);
    noInterrupts();

    // start 10 us pulse
    digitalWrite(TRIGGER_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGGER_PIN, LOW);
   
    int pulse = pulseIn(ECHO_PIN, HIGH, MAX_DUR +1000 ); // determine the time
    dur += pulse;
    Serial.print("[");
    Serial.print(pulse);
    Serial.print("]");

    interrupts();
  }

  if (dur > 0) {
    dur = dur / interval;

      Serial.print("(");
    Serial.print(dur);
    Serial.print(")");
  }

  if (dur < MIN_DUR) {
    return TO_SMALL;
  }
  
  if (dur > MAX_DUR ) {
    return TO_BIG;
  }
  
  return dur;
}

void initDist() {
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

/** get the distance in centi meter*/
double getDistCM(long dur) {
  return (dur / SC_CM);
}

// *************************************************

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    delay(1); // wait until the serial is ok (only for Leonardo)
  }
  initDist();
}

void loop () {

  Serial.print("Current distance is: ");
  long dur = getDur(5);

  if (dur > TO_SMALL) Serial.println(getDistCM(dur));
  else if ( dur == TO_BIG) Serial.println("TO FAR");
  else if ( dur == TO_SMALL) Serial.println("TO NEAR");
  delay(1000); // wait a second
}

