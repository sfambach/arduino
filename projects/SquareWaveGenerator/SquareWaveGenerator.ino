/******************************************************************************
# Description
SquareWaveGenerator

##Settings

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
// XXXXXXXX

/*****************************************************************************/
// XXXXXXXX

/*****************************************************************************/
// XXXXXXXX

/*****************************************************************************/
// XXXXXXXX

/*****************************************************************************/
// XXXXXXXX

const uint8_t pin[] = { 7, 8, 9, 10, 11, 12, 13 };
bool pin_state[] = { false, false, false, false, false, false, false };

long currentTime;
long lastTime;

/*****************************************************************************/
// Main Programm

void setup() {
  Serial.begin(115200);
  DEBUG_PRINTLN("Setup");
  //pinMode(7, OUTPUT);
  for (int i = 0; i < sizeof(pin)/sizeof(uint8_t); i++) {
    pinMode(pin[i], OUTPUT);
    pin_state[i]=false;
  }
  
  lastTime = millis();
}
bool state = false;
bool state2 = false;
int counter = 0;

void loop() {

  bool shoot = false;

  currentTime = millis();


  if (lastTime + 100 <= currentTime ) {
    lastTime = currentTime;
    counter++;
    shoot = true;
  }
  if(!shoot){
    return;
  }
  int divisor = 1;
  for (int i = 0; i < sizeof(pin)/sizeof(uint8_t); i++) {

    if(counter% (divisor) == 0){
      pin_state[i] = !pin_state[i];
      digitalWrite(pin[i], pin_state[i]);
    }
    divisor *=2;
  }

}

/*****************************************************************************/
// Rest of implementations