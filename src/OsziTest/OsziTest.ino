/******************************************************************************
* Oszilloscope Test
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

/** Select Test****************************************************************/

#define BLOCKING_BLINK
//#define NONE_BLOCKING_BLINK
//#define PWM
//#define UART
//#define I2C
//#define DHT


uint8_t BLOCKING_PIN = 19;



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
#define PWM1_Ch    0
#define PWM1_Res   8
#define PWM1_Freq  1000
int PWM1_DutyCycle = 100; 

void progPwm(){
  while(PWM1_DutyCycle < 255)
  {
    ledcWrite(PWM1_Ch, PWM1_DutyCycle++);
    delay(100);
  }
  while(PWM1_DutyCycle > 0)
  {
    ledcWrite(PWM1_Ch, PWM1_DutyCycle--);
    delay(100);
  }
}


/** XXXXXXXX *****************************************************************/
/** Input  *****************************************************************/

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
char buffer[20];
int bufferCounter = 0;
bool initial = false;

void processInput(){
    if (Serial.available() < 1) {
      return;
    }

    int rec = Serial.read();
    
    if(rec == DELIMIT_LINE_FEED || rec == DELIMIT_NEW_LINE || rec == DELIMIT_ROLLBACK){
          // end of input so lets see what we have
           //DEBUG_PRINTLN(rec);
          if(bufferCounter > 0){ // there is something in the buffer!
             
             switch(buffer[0]){
              case PROG_HELP: help(); break;
              case PROG_BLINK: currentProg = PROG_BLINK;
                  savedTime = 0;
               /* int arg1 = atoi(argv1);
                if(arg1 > 0 ){
                  delayMillis = arg1
                }
                
                atoi(buffer[1]);*/
                break;
              case PROG_PWM: currentProg = PROG_PWM;
              initial = true;
              ledcAttachPin(PIN, PWM1_Ch);
              ledcSetup(PWM1_Ch, PWM1_Freq, PWM1_Res);
              break;
              
             }
             
         
          }  
          bufferCounter = 0;
        } else {
          buffer[bufferCounter]= rec;
          bufferCounter++;
        }
}


/** Main Programm ************************************************************/

void setup() {
  // init serial port for output
  Serial.begin(115200);

  // set pin to output 
  pinMode(PIN, OUTPUT);

  // sow the help text
  help();
  
}





void loop() {

      processInput();

      switch(currentProg){
              case PROG_BLINK: progBlink(); break;
              case PROG_PWM:   progPwm();   break;   
      }
}

void serialEvent(){
  //DEBUG_PRINTLN("Serial Event");
}

/** Rest of implementations **************************************************/