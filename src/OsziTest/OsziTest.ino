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

uint8_t PIN = 19;


const char PROG_HELP  = 'h';
const char PROG_BLINK = 'b'; // blinks
const char PROG_PWM   = 'p';


const char DELIMIT_NEW_LINE = '\n';
const char DELIMIT_ROLLBACK =  '\r';
const char DELIMIT_LINE_FEED = '\0';
const char DELIMIT_SPACE = ' ';
  
char currentProg = PROG_BLINK;

char argv1[10];
char argv2[10];
//mainProgCalls



/** HELP *********************************************************************/

void help(){

  Serial.println( F("h - This help text \n"));
  Serial.println( F("b - (default after start) blink \n"));
  Serial.println( F("h - This help text \n"));

}


/** BLINK ********************************************************************/
long savedTime = 0 ; 
long delayMillis = 100;
bool state = false;

void progBlink(){
  if( (savedTime + delayMillis) < millis()){
    state = !state;
    digitalWrite(PIN,state);
    savedTime = millis();
  }


}

/** PWM **********************************************************************/
void progPwm(){


}


/** XXXXXXXX *****************************************************************/
/** XXXXXXXX *****************************************************************/


/** Main Programm ************************************************************/
char buffer[20];
int bufferCounter = 0;
void setup() {
  // init serial port for output
  Serial.begin(115200);

  // set pin to output 
  pinMode(PIN, OUTPUT);

  // sow the help text
  help();
  
}


bool initial = true;
void loop() {

    if (Serial.available() > 0) {
        int rec = Serial.read();
        //DEBUG_PRINTLN(rec);
        if(rec == DELIMIT_LINE_FEED || rec == DELIMIT_NEW_LINE || rec == DELIMIT_ROLLBACK){
          // end of input so lets see what we have
           //DEBUG_PRINTLN(rec);
          if(bufferCounter > 0){ // there is something in the buffer!
             
             switch(buffer[0]){
              case PROG_HELP: help(); break;
              case PROG_BLINK: currentProg = PROG_BLINK;
                int arg1 = atoi(argv1);
                if(arg1 > 0 ){
                  delayMillis = arg1
                }
                savedTime = 0;
                atoi(buffer[1]);
                break;
              case PROG_PWM: currentProg = PROG_PWM;
              break;
              
             }
             
         
          }  
          bufferCounter = 0;
        } else {
          buffer[bufferCounter]= rec;
          bufferCounter++;
        }
     } else {
        switch(currentProg){
              case PROG_BLINK: progBlink(); break;
              case PROG_PWM:   progPwm();   break;   
        }

     }
}

void serialEvent(){
  //DEBUG_PRINTLN("Serial Event");
}

/** Rest of implementations **************************************************/