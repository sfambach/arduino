/******************************************************************************
* PCF8574 Output Test 
* Write test for the io ports 
* I used 2 RGB LED to display the result.
* Connection 
* P0 --- LED 1 Blue
* P1 --- LED 1 Green
* P2 --- LED 1 Red
* P3 --- LED 2 Blue
* P4 --- LED 2 Green
* P5 --- LED 2 Red
*
* Licence: AGPL3
* Author: S. Fambach
* Visit http://www.fambach.net if you want
******************************************************************************/


/** Debuging *****************************************************************/
#define DEBUG
#ifdef DEBUG
#define DEBUG_PRINTLN(x) Serial.println(x)
#define DEBUG_PRINT(x) Serial.print(x)
#else
#define DEBUG_PRINTLN(x)
#define DEBUG_PRINT(x)
#endif


/** PCF8574.h *****************************************************************/
#include "PCF8574.h"

PCF8574 pcf(0x20);
#define MAX_PORT 6  // only use the 6 first ports+

/** Main Programm ************************************************************/
void setup() {
  Serial.begin(115200);
  DEBUG_PRINTLN("Setup");

  pcf.begin();
}

int i = 0;
void loop() {

  // delete old output
  for (int d = 0; d < MAX_PORT; d++) {
    pcf.write(d, LOW);
  }

  pcf.write(i, HIGH);
  delay(1000);
  i++;
  // If you are at the end, start again at the beginning
  if (i == MAX_PORT) {
    i = 0;
  }
}


/** Rest of implementations **************************************************/
