/******************************************************************************
* PCF8574 Input Test 
* Read the 8 io ports and display the status
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


/** Main Programm ************************************************************/
void setup() {
  Serial.begin(115200);
  DEBUG_PRINTLN("Setup");

  pcf.begin();
 
}


void loop() {
  int x = pcf.read8();
  Serial.print("Read ");
  Serial.println(x, BIN);
  delay(1000);
}


/** Rest of implementations **************************************************/