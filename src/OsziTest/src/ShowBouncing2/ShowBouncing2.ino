/******************************************************************************
# Show the bouncing of a button switch
 Input is simply redirected to output and the closure of button is counted
 Press the button once and you might see that the ouput counter will be 
 increase more than one time. You cannot observer this each and every time you 
 have to test it some times to get the result.
 ## Settings
 Define input and ouput pin
* PIN_IN (Default GPIO18) - Input for the button
* PIN_OUT (Default GPIO 19) - Output for measurement and/or LED
 
## Credits
* Licence: AGPL3
* Author: S. Fambach
Visit http://www.fambach.net if you want
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


/** Globals ******************************************************************/
#define PIN_IN  18
#define PIN_OUT 19
long countIn = 0;
bool oldIn = false;

/** Main Programm ************************************************************/
void setup() {
  Serial.begin(115200);           // init serial port

  //pinMode(PIN_IN,INPUT_PULLUP); // activate this to invert the input
  pinMode(PIN_IN,INPUT);          // set to input 
  pinMode(PIN_OUT,OUTPUT);        // set to output
}

void loop() {

  // read the input 
  bool in = digitalRead(PIN_IN); 
  
  // simply write 1:1 the output
  digitalWrite(PIN_OUT,in); 

  // check only for pressed if the value has changed
  if(in && in != oldIn){
      // increase button press counter
      countIn ++;           
  } 
    
  // save the current value
  oldIn = in;

  // output the current value
  DEBUG_PRINTLN(countIn);
}

