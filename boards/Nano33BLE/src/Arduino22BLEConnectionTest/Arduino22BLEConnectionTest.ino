#include <ArduinoBLE.h>

/******************************************************************************
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


/** XXXXXXXX *****************************************************************/
/** XXXXXXXX *****************************************************************/
/** XXXXXXXX *****************************************************************/
/** XXXXXXXX *****************************************************************/
/** XXXXXXXX *****************************************************************/


/** Main Programm ************************************************************/
void setup() {
  Serial.begin(115200);
  DEBUG_PRINTLN("Setup");
}


void loop() {
  DEBUG_PRINT("Simulate Buttons");
  DEBUG_PRINTLN("Press Buttons");

  delay(500);
  DEBUG_PRINTLN("Release Buttons");

  delay(500);
}

void serialEvent(){
  DEBUG_PRINTLN("Serial Event");
}

/** Rest of implementations **************************************************/