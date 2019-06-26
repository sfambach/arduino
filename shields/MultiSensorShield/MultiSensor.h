#ifndef multi_senosor_h
#define multi_senosor_h
/********************************************************/
#include "DHT.h"
#include "EasyBuzzer.h"

/********************************************************/


#define SWITCH1   2
#define SWITCH2   3
#define DHT11_PIN 4
#define BUZZER    5
#define IR        6
#define ADDPIN1   7
#define ADDPIN2   8
#define RGB_RED   9
#define RGB_GREEN 10
#define RGB_BLUE  11
#define LED_RED   12
#define LED_BLUE  13

#define POTI  A0
#define LDR   A1
#define LM35  A2

class MultiSensor {

  private:
    DHT _dht11;

    int _curProg = 0;
    const int _maxProg = 10;

  public:
    enum Color {
      OFF, RED, GREEN, BLUE, YELLOW, MAGENTA, CYAN, ALL
    };
    MultiSensor() : _dht11(DHT11_PIN, DHT11) {}
    void init() {

      // init pins
      pinMode( SWITCH1, INPUT);
      pinMode( SWITCH2, INPUT);
      pinMode( DHT11, INPUT);
      pinMode( BUZZER, OUTPUT);
      pinMode( IR , INPUT);
      //pinMode( ADDPIN1, INPUT);
      //pinMode( ADDPIN2 , INPUT);
      pinMode( RGB_RED, OUTPUT);
      pinMode( RGB_GREEN, OUTPUT);
      pinMode( RGB_BLUE, OUTPUT);
      pinMode( LED_RED, OUTPUT);
      pinMode( LED_BLUE, OUTPUT);

      pinMode( POTI, INPUT);
      pinMode( LDR , INPUT);
      pinMode( LM35, INPUT);

      //_dht11.begin();

      //EasyBuzzer.setPin(BUZZER);
    }


    int getSwitch1() {
      boolean state = false;

      state  =  !digitalRead(SWITCH1);
      if (state) {
        _curProg ++;
        if (_curProg > _maxProg) {
          _curProg = 0;
        }
      }
      while (!digitalRead(SWITCH1));

      return _curProg;

    }


    int getSwitch2() {
      boolean state = false;

      state  =  !digitalRead(SWITCH2);
      if (state) {
        _curProg --;
        if (_curProg < 0) {
          _curProg = _maxProg;
        }
      }
      while (!digitalRead(SWITCH2));

      return _curProg;

    }
    double getDHT11Humidity() {
      return _dht11.readHumidity();
    }

    double getDHT11Temperature() {
      return _dht11.readTemperature();
    }

    double testBuzzer() {
      EasyBuzzer.beep(1000, 10); // freq 1000, 10 times.
    }


    void setRGBLed(Color color) {

      switch (color) {
        case RED:
          digitalWrite(RGB_RED, true);
          digitalWrite(RGB_GREEN, false);
          digitalWrite(RGB_BLUE, false);
          break;
        case GREEN:
          digitalWrite(RGB_RED, false);
          digitalWrite(RGB_GREEN, true);
          digitalWrite(RGB_BLUE, false);
          break;
        case BLUE:
          digitalWrite(RGB_RED, false);
          digitalWrite(RGB_GREEN, false);
          digitalWrite(RGB_BLUE, true);
          break;
        case MAGENTA:
          digitalWrite(RGB_RED, true);
          digitalWrite(RGB_GREEN, false);
          digitalWrite(RGB_BLUE, true);
          break;
        case CYAN:
          digitalWrite(RGB_RED, false);
          digitalWrite(RGB_GREEN, true);
          digitalWrite(RGB_BLUE, true);
          break;
        case YELLOW:
          digitalWrite(RGB_RED, true);
          digitalWrite(RGB_GREEN, true);
          digitalWrite(RGB_BLUE, false);
          break;
        case ALL:
          digitalWrite(RGB_RED, true);
          digitalWrite(RGB_GREEN, true);
          digitalWrite(RGB_BLUE, true);
          break;

        default:
          digitalWrite(RGB_RED, false);
          digitalWrite(RGB_GREEN, false);
          digitalWrite(RGB_BLUE, false);
      }
    }
    void setRedLED(boolean state) {
      digitalWrite(LED_RED, state?HIGH:LOW);
    }

    void setBlueLED(boolean state) {
      digitalWrite(LED_BLUE, state?HIGH:LOW);
    }



    int getPoti() {
      return map(analogRead(POTI), 0, 255, 0, 100);
    }


    int getLDR() {
      return map(analogRead(LDR), 0, 255, 0, 100);
    }

    int getLM35() {
      return map(analogRead(LM35),  0, 307, 0, 150);
    }

    void loop(boolean test = false) {
      EasyBuzzer.update();

      if (test) {
        setRedLED(getSwitch1());
        setBlueLED(getSwitch2());
        Serial.println(_curProg);

        switch (_curProg) {

          case 0: //setRedLED(true);
            Serial.println("Red led on");
            break;
          case 1: setRedLED(false);
            Serial.println("Red led off");
            break;
          case 2: setBlueLED(true);
            Serial.println("Blue led on");
            break;
          case 3: setBlueLED(false);
            Serial.println("Blue led off");
            break;

        }
      }

    }



};




#endif // multi_senosor_h
