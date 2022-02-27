/******************************************************************
   Car with PS2 remote controle
   Author: S. Fambach
   www.fambach.net

*/
#include <Wire.h>

/******************************************************************
   SR04
*/
#include "NewPing.h"
#define TRIGGER_PIN   8
#define ECHO_PIN      7
#define MAX_DISTANCE 300
#define MAX_DUR 123456
#define MIN_DUR 12
#define SC_CM 0.1

#define TO_SMALL 0x01
#define TO_BIG 0x02
NewPing sr04 (TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

const int POS = 0;
const int DIST = 1;

long timer = 0;
long movement = 0;
int fixSpeed = 100;

int distance[3] = { -1, -1, -1};
float val[3] = { -1, -1, -1};
int add = 1;
boolean distMeasure = false;
boolean gotValue = false;

void echoCheck() {
  if (sr04.check_timer()) {
    gotValue = true;
  }
}

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

/******************************************************************
   Motor
*/
#include "Adafruit_MotorShield.h"
Adafruit_MotorShield AFMS; // = Adafruit_MotorShield();

Adafruit_DCMotor* motorLeft = AFMS.getMotor(3);
Adafruit_DCMotor* motorRight = AFMS.getMotor(4);

const int STEER_MAX = 60;

void stop() {

  motorLeft->run(BRAKE);
  motorRight->run(BRAKE);

  // stop motoren
  motorLeft->setSpeed(0);
  motorRight->setSpeed(0);
}

void turnRight() {
  stop();
  motorLeft->run(FORWARD);
  motorRight->run(BACKWARD);
  motorLeft->setSpeed(fixSpeed);
  motorRight->setSpeed(fixSpeed);
  delay(200);
  stop();
}

void turnLeft() {
  stop();
  motorLeft->run(BACKWARD);
  motorRight->run(FORWARD);
  motorLeft->setSpeed(fixSpeed);
  motorRight->setSpeed(fixSpeed);
  delay(200);
  stop();
}
void forward() {
  motorLeft->run(FORWARD);
  motorRight->run(FORWARD);
  motorLeft->setSpeed(fixSpeed);
  motorRight->setSpeed(fixSpeed);
}

/******************************************************************
   Servos
*/
#include "Adafruit_PWMServoDriver.h"

// call the servo driver with the corretct address of the board.
// Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x60);not needed using afms to

#define MIN_PULSE  150
#define MAX_PULSE  480

#define MAX_DEG_X  150
#define MAX_DEG_Y  130
#define MIN_DEG_X  45
#define MIN_DEG_Y  70

#define SERVO_Y 0
#define SERVO_X 1

#define CORR_X -18
#define CORR_Y -25

int pos[3] = {90 + CORR_X - 40, 90 + CORR_X, 90 + CORR_X + 40};

void setServoPulse(uint8_t n, double pulse) {
  double pulselength;
  pulselength = 1000000;   // 1,000,000 us per second
  pulselength /= 50;   // 50 Hz
  // Serial.print(pulselength); Serial.println(" us per period");
  pulselength /= 4096;  // 12 bits of resolution
  // Serial.print(pulselength); Serial.println(" us per bit");
  pulse *= 1000;
  pulse /= pulselength;
  // Serial.println(pulse);
  AFMS.setPWM(n, pulse);
}

// Angle to PWM
void writeServo(uint8_t n, uint8_t angle) {
  double pulse;
  pulse = 0.5 + angle / 90.0;
  setServoPulse(n, pulse);
}



void yes() {
  // move servos to center
  writeServo(SERVO_X, 90 + CORR_X);
  writeServo(SERVO_Y, 90 + CORR_Y);

  int curX = 90 + CORR_X;
  int curY = 90 + CORR_Y;

  int d = 2;

  for (int i = 0 ; i < 50 ; i++) {
    curY--;
    writeServo(SERVO_Y, curY);
    delay(d);
  }


  for (int i = 0 ; i < 100 ; i++) {
    curY++;
    writeServo(SERVO_Y, curY);
    delay(d);
  }

  for (int i = 0 ; i < 50 ; i++) {
    curY--;
    writeServo(SERVO_Y, curY);
    delay(d);
  }

}

void no() {
  // move servos to center
  writeServo(SERVO_X, 90 + CORR_X);
  writeServo(SERVO_Y, 90 + CORR_Y);

  int curX = 90 + CORR_X;
  int curY = 90 + CORR_Y;

  int d = 2;

  for (int i = 0 ; i < 50 ; i++) {
    curX--;
    writeServo(SERVO_X, curX);
    delay(d);
  }


  for (int i = 0 ; i < 100 ; i++) {
    curX++;
    writeServo(SERVO_X, curX);
    delay(d);
  }

  for (int i = 0 ; i < 50 ; i++) {
    curX--;
    writeServo(SERVO_X, curX);
    delay(d);
  }

}

/******************************************************************
   PS2 Controller settings
*/

#include "PS2X_lib.h"  //for v1.8
#define PS2_DAT        12
#define PS2_CMD        11
#define PS2_SEL        10
#define PS2_CLK        13

#define pressures  false
#define rumble     true

PS2X ps2x;

int error = 0;
byte type = 0;
byte vibrate = 0;


const int MODE_RC = 0; // remote control
const int MODE_FD = 1; // free drive
int currentMode = MODE_RC;
bool controllerFound = false;


bool initGamepad() {

  if (controllerFound) {
    return true;
  }
  // so not configured now try to init
  // setup pins and settings: GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
  error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);
  if (error == 0) {
    Serial.print("Found Controller, configured successful ");
    Serial.print("pressures = ");
    if (pressures)
      Serial.println("true ");
    else
      Serial.println("false");
    Serial.print("rumble = ");
    if (rumble)
      Serial.println("true)");
    else
      Serial.println("false");

    type = ps2x.readType();
    switch (type) {
      case 0:
        Serial.print("Unknown Controller type found ");
        break;
      case 1:
        Serial.print("DualShock Controller found ");
        break;
      case 2:
        Serial.print("GuitarHero Controller found ");
        break;
      case 3:
        Serial.print("Wireless Sony DualShock Controller found ");
        break;
    }
    controllerFound = true;
    return true;
  }
  else if (error == 1)
    Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");

  else if (error == 2)
    Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");

  else if (error == 3)
    Serial.println("Controller refusing to enter Pressures mode, may not support it. ");
  return false;
}

/******************************************************************/
// Programs
uint8_t curDir = FORWARD;
int maxg = 200;
// remote controlled driving
void rcDrive() {


  //  motor[curMotor]->run(dir[curDir]);
  int speed = ps2x.Analog(PSS_LY); // geschwindigkeit bestimmen
  int steering = ps2x.Analog(PSS_RX); // lenkung bestimmen

  int leftSubstactor = 0;
  int rightSubstactor = 0;

  // lenkung
  if (steering < 125) {
    steering = map(steering, 127, 0, 0, -STEER_MAX);
    leftSubstactor = steering;

  } else if (steering > 130) {
    steering = map(steering, 127, 255, 0, -STEER_MAX);
    rightSubstactor = steering;
  } else {
    steering = 0;
  }


  // geschwindigkeit ermitteln
  if (speed < 125) {
    speed = map(speed, 127, 0, 0, maxg);
    motorLeft->setSpeed(speed + leftSubstactor);
    motorRight->setSpeed(speed + rightSubstactor);

    if (curDir != FORWARD) {
      stop();
      delay(100);
      curDir = FORWARD;
    }

    motorLeft->run(FORWARD);
    motorRight->run(FORWARD);


  } else if (speed > 130) {
    speed = map(speed, 127, 255, 0, maxg);
    motorLeft->setSpeed(speed + leftSubstactor);
    motorRight->setSpeed(speed + rightSubstactor);

    if (curDir != BACKWARD) {
      stop();
      delay(100);
      curDir = BACKWARD;
    }

    motorLeft->run(BACKWARD);
    motorRight->run(BACKWARD);

  } else {
    speed = 0;
    motorLeft->setSpeed(speed);
    motorRight->setSpeed(speed);
    delay(100);

  }

  Serial.print("Aktuelle Werte: ");
  Serial.print("SpeedLeft = ");
  Serial.print(speed + leftSubstactor, DEC);
  Serial.print(" SpeedRight = ");
  Serial.print(speed + rightSubstactor, DEC);
  Serial.print(" Lenkeinschlag = ");
  Serial.print(steering, DEC);
  //  Serial.print("");
  Serial.println("");

}

const int SERVO = 0;
const int MEASURE = 1;
const int WAIT_RESULT = 2;

const int MOVEMENT_TIME = 1000; // one second to move the servo
int servoTimer   = 0;
void moveServo(int loc) {
  writeServo(SERVO_X, pos[loc]);
  servoTimer =  millis() + MOVEMENT_TIME;
}

int measureTimer = 0;
int state = 0;
int curPos = 0;
int dir = +1;
bool gotAllValues = false;

void freeDrive() {

  // check if its time to turn the servo
  if (state == SERVO) {
    Serial.println("drive servo");
    moveServo(curPos);
    state++;
  }

  // check if its time to start measurement
  if (state == MEASURE && servoTimer < millis()) {
    Serial.println("measurement");
    //sr04.ping_timer(echoCheck);
    long dur = getDur(5);
    state++;
  }

  // check if measurement is there
  if (state == WAIT_RESULT && gotValue) {
    Serial.println("Got measurement");
    gotValue = false;
    sr04.timer_stop();
    val[curPos] = sr04.ping_result;
    state = SERVO;

    curPos += dir;
    if (curPos > 2 || curPos < 0) {
      Serial.println("Change servo direction");
      curPos = 1;
      dir = -dir;
      gotAllValues = true;
    }
  }


  // drive servo to corect pos
  if (gotAllValues) {
    gotAllValues = false;
    // do something with the measurement
    Serial.print("dr:\t");
    Serial.print(val[0]);
    Serial.print(" dc:\t");
    Serial.print(val[1]);
    Serial.print(" dl:\t");
    Serial.println(val[2]);

    // turn in the longest direction

    //    if (val[1] < val[0] || val[1] < val[2]) {
    //
    //      if (val[0] > val[2]) {
    //        turnRight();
    //      } else {
    //        turnLeft();
    //      }
    //    } else {
    //      forward();
    //    }
  }
}



void setup() {

  Serial.begin(115200);
  delay(300);

  /******************************************************************/
  /* distgance*/
  //sr04.init();
 initDist();
  /******************************************************************/
  /* Motor */
  AFMS.begin(50);// 50hz is the standard (for the servos)
  delay(300);

  yes();

  // some output after reset
  if (MCUSR & (1 << WDRF)) {
    Serial.println("a watchdog reset occurred");
    delay(5000);
  }
  if (MCUSR & (1 << BORF)) {
    Serial.println("a brownout reset occurred");
    delay(5000);
  }
  if (MCUSR & (1 << EXTRF)) {
    Serial.println(" an external reset occurred");
    delay(5000);
  }
  if (MCUSR & (1 << PORF)) {
    Serial.println(" a power on reset occurred");
    delay(5000);
  }
}

bool firstReading = true;
void loop() {

  //skip loop as long as no controller found
  if (!initGamepad()) {
    delay(2000);
    Serial.println("ohoho");
    return;
  }

  // get the type of controller
  type = ps2x.readType();

  // check if type is supported
  if (type != 1) {
    Serial.print("Wrong type : ");
    Serial.println(type);
    return;
  }

  ps2x.read_gamepad(false, vibrate); //read controller and set large motor to spin at 'vibrate' speed

  // skip the first reading, its non-sense
  if (firstReading) {
    firstReading = false;
    return;
  }

  // PSB_START, PSB_SELECT, PSB_PAD_UP, PSB_PAD_RIGHT, PSB_PAD_LEFT, PSB_PAD_DOWN

  // zuerst den Modus überprüfen dann handen.
  if (ps2x.NewButtonState(PSB_CIRCLE)) {
    Serial.println("Free Drive Modus aktiviert");
    stop();
    currentMode = MODE_FD;
    vibrate = 255;

  } else if (ps2x.NewButtonState(PSB_SQUARE)) {
    Serial.println("RC Modus aktiviert");
    stop();
    currentMode = MODE_RC;
    vibrate = 255;

  } else if (ps2x.NewButtonState(PSB_CROSS)) {
    no();
  } else if (ps2x.NewButtonState(PSB_TRIANGLE)) {
    yes();
  }

  if (ps2x.ButtonReleased(PSB_CIRCLE) ||
      ps2x.ButtonReleased(PSB_SQUARE) ||
      ps2x.ButtonReleased(PSB_CROSS) ||
      ps2x.ButtonReleased(PSB_TRIANGLE) ) {
    vibrate = 0;
  }

  switch (currentMode) {
    case MODE_RC: rcDrive(); break;
    case MODE_FD: freeDrive(); break;
  }
  delay(50);
}
