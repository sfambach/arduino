/******************************************************************************
* Test Soft and Hardware debouncing
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

#define PIN_IN  18
#define PIN_OUT 19
#define PIN_LIGHT 17
/** XXXXXXXX *****************************************************************/
/** XXXXXXXX *****************************************************************/
/** XXXXXXXX *****************************************************************/
/** XXXXXXXX *****************************************************************/


/** Main Programm ************************************************************/
void setup() {
  Serial.begin(115200);
  DEBUG_PRINTLN("Setup");
  //pinMode(PIN_IN,INPUT_PULLUP);
  pinMode(PIN_IN,INPUT);
  pinMode(PIN_OUT,OUTPUT);
  pinMode(PIN_LIGHT,OUTPUT);
}

long inCount =0;
bool oldIn = false;
void loop() {
  bool in = digitalRead(PIN_IN);
  
  digitalWrite(PIN_OUT,in);
  //digitalWrite(PIN_LIGHT,!in);
  if(in){
    inCount++;
   // if(in != oldIn) {
      DEBUG_PRINTLN(inCount);
  //}    
  }else {
    DEBUG_PRINTLN(0);
    //digitalWrite(PIN_LIGHT,!in);
  }
  oldIn = in;
}

void serialEvent(){
  DEBUG_PRINTLN("Serial Event");
}

/** Rest of implementations **************************************************/