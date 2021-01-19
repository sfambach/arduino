/** OpenSmart Uno test class 
 *  This is a small test calls for the Open Smart uno board.
 *  It is a uno compatible board with discrete parts and 
 *  3 additional leds as well 3 switches and a buzzer.
 *  
 *  www.fambach.net
 *  GPLv2
 */

#ifndef OpenSmartUnoR3_h
#define OpenSmartUnoR3_h
#include "EasyBuzzer.h"

#define BUZZER 6

class OpenSmartUnoR3 {

  protected:
   bool _test;
   EasyBuzzerClass eb;

  public:
    enum SWITCH {
      SW1 = 2,
      SW2 = 3,
      SW3 = 4
    };

    enum LED {
      LED1 = 7,
      LED2 = 8,
      LED3 = 13
    };

    void init(bool test = false) {
      _test = test;
      pinMode(LED1, OUTPUT);
      pinMode(LED2, OUTPUT);
      pinMode(LED3, OUTPUT);
      pinMode(BUZZER, OUTPUT);

      pinMode(SW1, INPUT_PULLUP);
      pinMode(SW2, INPUT_PULLUP);
      pinMode(SW3, INPUT_PULLUP);
    }

    void loop() {
      if (_test) {
          setLED(LED1, getSwitch(SW1));
          setLED(LED2, getSwitch(SW2));
          setLED(LED3, getSwitch(SW3));

          if(getSwitch(SW1) && getSwitch(SW2)){
            eb.beep(1000);
          }else {
            eb.stopBeep();
          }
      }
    }

    bool getSwitch(SWITCH sw) {
        return !digitalRead(sw);
    }

    static void setLED(LED selected, bool status) {
        digitalWrite(selected, status);
    }

    

};

OpenSmartUnoR3 Board;

#endif // OpenSmartUnoR3_h
