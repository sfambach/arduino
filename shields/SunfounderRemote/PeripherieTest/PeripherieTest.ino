// Sunfounder Remote test of Joystick
// www.fambach.net
// GPL2
//***************************************************

boolean pressed = false;
const byte PIN_BUTTON = 2;
const byte PIN_ANALOG_X = A1;
const byte PIN_ANALOG_Y = A0;
int analog_x = 512;
int analog_y = 512;

const int MIN_DELTA = 4;

void setup() {
  Serial.begin(9600);
  pinMode(PIN_BUTTON, INPUT);
}

void loop() {
  bool changed = false;

  // get button states
  boolean b = digitalRead(PIN_BUTTON);
  if (b != pressed) {
    pressed = b;
    changed = true;
  }

  int cur = analogRead(PIN_ANALOG_X );
  int delta = analog_x - cur;

  if ( delta > MIN_DELTA || delta < -MIN_DELTA) {
    analog_x = cur;
    changed = true;
  }

  cur = analogRead(PIN_ANALOG_Y );
  delta = analog_y - cur;

  if ( delta > MIN_DELTA || delta < -MIN_DELTA ) {
    analog_y = cur;
    changed = true;
  }

  if (changed) {
    Serial.print("Button: ");
    Serial.print(pressed);
    Serial.print(" X: ");
    Serial.print(analog_x);
    Serial.print(" Y: ");
    Serial.println(analog_y);
  }

}
