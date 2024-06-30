/******************************************************************************
# 4 Digets 7 Segment Display

##Settings
Ports for the Display

## Credits 
* Licence: AGPL3
* Author:  S. Fambach
Visit http://www.fambach.net if you want
******************************************************************************/

/*****************************************************************************/
// Debuging

#define DEBUG
#ifdef DEBUG
#define DEBUG_PRINTLN(x) Serial.println(x)
#define DEBUG_PRINT(x) Serial.print(x)
#else
#define DEBUG_PRINTLN(x)
#define DEBUG_PRINT(x)
#endif

/*****************************************************************************/
// Setup display
#include <TimerOne.h>
#include <MultiFuncShield.h>

const int ACS712_Pin = A0;
const int zeroCurrentValue = 510;
/*****************************************************************************/
// XXXXXXXX

/*****************************************************************************/
// XXXXXXXX

/*****************************************************************************/
// XXXXXXXX


/*****************************************************************************/
// Main Programm

void setup() {
  Serial.begin(115200);
  DEBUG_PRINTLN("Setup");
 
  Timer1.initialize();
  MFS.initialize(&Timer1); 

  char text[]={'E','E','E','E'};
  MFS.write(text, false);
  
/*  delay(2000);
  char text2[]={'-','-','-','-'};
  MFS.write(text2, false);
  delay(2000);
  MFS.write(2.0f, 3);
*/
  // pinMode(ACS712_Pin,INPUT);
}

void loop() {
  int rawValue = analogRead(ACS712_Pin);
  float val = 0.0f;

  if(rawValue > zeroCurrentValue){
    val = (rawValue - zeroCurrentValue)* 5.0/1.024 /0.185;
  } else {
    val = -((zeroCurrentValue - rawValue)); //* 5.0/1.024 /0.185);
  }

  Serial.print(rawValue);
  Serial.print( " -> ");
  Serial.println(val);
  MFS.write(val, 3);
  delay(100);
}

// activate for serial event
/*void serialEvent(){
  DEBUG_PRINTLN("Serial Event");
}*/

/*****************************************************************************/
// Rest of implementations