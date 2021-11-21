/** Test the Open-Smart Wireless Joystick
 *  Receiver program
 * http://www.fambach.net
 * GPL v2
 */
 
#include <String.h>
#include "VirtualWire.h"

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

uint8_t decode()
{
  Serial.print("RAW : \t");
  for(int i = 0; i < buflen ; i++){
    Serial.print(buffer[i],HEX);
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
  uint8_t button;
  uint8_t i = 0;
  x = buffer[1]<<2 ;
  y = buffer[2]<<2 ;
  button = buffer[3] ;

  Serial.print(" X:\t");
  Serial.print(x);
  Serial.print(" Y:\t");
  Serial.print(y);

  Serial.print(" Button:\t");
  switch (button)
  {    
    case 1: command = BUTTON_UP;
    Serial.print("K1");
    break;
    case 2: command = BUTTON_RIGHT; 
    Serial.print("K2");break;
    case 3: command = BUTTON_DOWN;
    Serial.print("K3");break;
    case 4: command = BUTTON_LEFT; 
    Serial.print("K4");break;
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

