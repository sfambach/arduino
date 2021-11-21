/** Test the Open-Smart Wireless Joystick
    Receiver program
   http://www.fambach.net
   GPL v2
*/

#include <String.h>
#include "VirtualWire.h"

/*******************************************************************/
#include "AFMotor.h"

// motors
AF_DCMotor mright(2);
AF_DCMotor mleft(3);


/*******************************************************************/
// servo config
#ifdef PAN_TILT
#include <Servo.h>

Servo servoX;
Servo servoY;


int xMin = 20;
int yMin = 20;
int xMax = 200;
int yMax = 200;
int xCur = 122;
int yCur = 122;
int step = 20;

#endif

/*******************************************************************/


int RF_RX_PIN = A3;
void(* resetFunc) (void) = 0; //software reset when the RF receiver can not respond

//Remote control code macro
#define BUTTON_UP     1
#define BUTTON_RIGHT  2
#define BUTTON_DOWN   3
#define BUTTON_LEFT   4
#define BUTTON_JOY    8


#define XY_TOLERANCE 30
#define X0 510 //Initial value of X-asix of the Joystick
#define Y0 510 //Initial value of Y-asix of the Joystick

#define SPEED_STEPS 20
uint8_t speed0 = 100;//Initial value of speed

#define BIN1 3
#define BIN2 5
#define PWMB 6
#define AIN1 9
#define AIN2 10
#define PWMA 11

uint8_t buffer[VW_MAX_MESSAGE_LEN]; // buffer array for data recieve over serial port
uint8_t buflen = VW_MAX_MESSAGE_LEN;

void setup() {
  Serial.begin(115200);
  vw_set_rx_pin(RF_RX_PIN);  // Setup receive pin.
  vw_setup(2000); // Transmission speed in bits per second.
  vw_rx_start(); // Start the PLL receiver.
#ifdef PAN_TILT
  servoX.attach(9);
  servoY.attach(10);

  servoX.write(xCur);
  servoY.write(yCur);
#endif

  pinMode(A1,OUTPUT);

}
uint8_t command;

#define CAR_STOP 0
#define CAR_FORWARD 1
#define CAR_BACK 2
uint8_t car_status = CAR_STOP;
uint8_t new_status = car_status;



void loop() {
  if (vw_get_message(buffer, &buflen)) // non-blocking I/O
  {
    command = decode();

    Serial.print("\n");
  }

}

  uint8_t button;
uint8_t decode()
{
  Serial.print("RAW : \t");
  for (int i = 0; i < buflen ; i++) {
    Serial.print(buffer[i], HEX);
    Serial.print(" ");
  }
  Serial.print( "-> ");

  if ((buffer[0] != 0x7E) || (buffer[4] != 0xEF))
  {
    resetFunc();//software reset
    return 0;
  }
  int x, y;
  int xh, xl, yh, yl;
  uint8_t z;

  uint8_t i = 0;
  x = buffer[1] << 2 ;
  y = buffer[2] << 2 ;


  //--------------------------------------------------------
  // drive

  int curSpeed =  map(y, 0, 1024, -245, 245);
  int curDir = map(x, 0, 1024, -10, 10);
Serial.print("speed: ");
Serial.print(curSpeed);


  int leftDelta = 0;
  int rightDelta = 0 ;
  if(curDir < 0){
    leftDelta = -curDir;
    rightDelta = curDir;
  } else {
    leftDelta = -curDir;
    rightDelta = curDir;
  }

Serial.print(" dl: ");
Serial.print(leftDelta);

Serial.print(" dr: ");
Serial.print(rightDelta);

int speedl = 0;
int speedr = 0;

  if (curSpeed < 40 && curSpeed > -40) {
    curSpeed = 0;
    mleft.setSpeed(0);
    mright.setSpeed(0);
  } else if (curSpeed < 20) {
    mleft.run(BACKWARD);
    mright.run(BACKWARD);
    speedl =-curSpeed+leftDelta;
    speedr =-curSpeed+rightDelta;
        
  } else {
    mleft.run(FORWARD);
    mright.run(FORWARD);
    speedl =curSpeed+leftDelta;
    speedr =curSpeed+rightDelta;
       
  }

  mleft.setSpeed(speedl);
  mright.setSpeed(speedr);

Serial.print("/tspeedl/r: ");
Serial.print(speedl);

Serial.print(" / ");
Serial.print(speedr);

  //--------------------------------------------------------



  button = buffer[3] ;

  Serial.print(" X:\t");
  Serial.print(x);
  Serial.print(" Y:\t");
  Serial.print(y);

  Serial.print(" Button:\t");



if(button == BUTTON_JOY  ){
  Serial.println("Schuss");
  digitalWrite(A1, true);
}else {
  digitalWrite(A1, false);
}

  
  switch (button)
  {

#ifdef PAN_TILT
    case 1: command = BUTTON_UP;
      Serial.print("K1-UP");
      xCur += step;
      if (xCur > xMax) {
        xCur = xMax;
      }
      servoX.write(xCur);

      break;
#endif
    case 2: command = BUTTON_RIGHT;
      Serial.print("K2"); break;

#ifdef PAN_TILT
    case 3: command = BUTTON_DOWN;
      Serial.print("K3- Down"); break;
      xCur -= step;
      if (xCur < xMin) {
        xCur = xMin;
      }
      servoX.write(xCur);
#endif

    case 4: command = BUTTON_LEFT;
      Serial.print("K4"); break;
    case 8: command = BUTTON_JOY; break;
      Serial.print("Z-Joy");
    default: break;
  }
  clearBufferArray();
  return command;
}


void clearBufferArray()              // function to clear buffer array
{
  for (int i = 0; i < VW_MAX_MESSAGE_LEN; i++)
  {
    buffer[i] = 0; // clear all index of array with 0
  }
}
