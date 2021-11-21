/** Test the Open-Smart Wireless Joystick
 *  Receiver program
 *  Autor: S. Fambach
 *  Visit if you want: http://www.fambach.net
 *  GPL v2
 */
 
#include <String.h>
#include "VirtualWire.h"

int RF_RX_PIN = A3;
void(* resetFunc) (void) = 0; //software reset when the RF receiver can not respond
const char* TEMPLATE_OUTPUT = "RAW :  %s  ->  X:  %4.0d | Y:  %4.0d | Button: %s";
char outputText[50];


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

uint8_t buf[VW_MAX_MESSAGE_LEN]; // buffer array for data recieve over serial port
uint8_t buflen = VW_MAX_MESSAGE_LEN;

void setup() {
  Serial.begin(115200);

  Serial.println("Setup A3 Pin for Transmission");
  vw_set_rx_pin(RF_RX_PIN);  // Setup receive pin.
  Serial.println("Setup Transmission speed to 2000");
  vw_setup(2000); // Transmission speed in bits per second.
  Serial.println("Start receiving");
  vw_rx_start(); // Start the PLL receiver.
}
uint8_t command;

#define CAR_STOP 0
#define CAR_FORWARD 1
#define CAR_BACK 2
uint8_t car_status = CAR_STOP;
uint8_t new_status = car_status;


int msToWait = 2000;
int storedTime = millis() + msToWait;

void loop() {
  if (vw_get_message(buf, &buflen)) // non-blocking I/O
  {
    command = decode();
    Serial.print("\n");
    storedTime = millis() + msToWait; // reset timeout
  }

  if(storedTime < millis() ){
    Serial.println("Nothing received since 2 Seconds");
    storedTime = millis() + msToWait; // reset timeout
  }
 
}

uint8_t decode()
{
  String raw;
  int x, y;
  int xh, xl, yh, yl;
  uint8_t z;
  uint8_t button;
  uint8_t i = 0;

  // extract raw data 
  raw.reserve(10);
  for(int i = 0; i < buflen ; i++){
    raw += String(buf[i],HEX);
    raw += String(" ");
  }
   
  if ((buf[0] != 0x7E) || (buf[4] != 0xEF))
  {
    resetFunc();//software reset
    return 0;
  }

  // split data
  x = buf[1] << 2 ;
  y = buf[2] << 2 ;
  button = buf[3] ;

  // get special buttons
  String butText = "";
  switch (button)
  {    
    case 1: command = BUTTON_UP; butText="K1";break;
    case 2: command = BUTTON_RIGHT; butText="K2";break;
    case 3: command = BUTTON_DOWN;butText="K3";break;
    case 4: command = BUTTON_LEFT; butText="K4";break;
    case 8: command = BUTTON_JOY; butText="Joy";break;
    default: butText = button;
    
  }

  sprintf(outputText, TEMPLATE_OUTPUT , raw.c_str(),x,y,butText.c_str());
  Serial.println(outputText);

  
  clearBufferArray();
  return command;
}


void clearBufferArray()              // function to clear buffer array
{
  for (int i = 0; i < VW_MAX_MESSAGE_LEN; i++)
  {
    buf[i] = 0; // clear all index of array with 0
  }
}
