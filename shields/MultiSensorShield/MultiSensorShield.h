#ifndef multi_senosor_h
#define multi_senosor_h
/********************************************************/

#include "DHT.h"
#include "EasyBuzzer.h"
#include "boarddefs.h"
#include <IRremote.h>


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

int RECV_PIN = IR;

char* codeNames[] {"Schuss", "RED", "GREEN", "BLUE", "YELLOW", "MAGENTA", "CYAN","ON"};
long codes[] {0xFF6897, 0xFF6897, 0xFF9867, 0xFFB04F, 0xFF4AB5, 0xFF42BD, 0xFF5AA5, 0xFFA25D};


class MultiSensor {

  private:
    DHT _dht11;
    IRrecv _ir;
    decode_results _results;
    int _curProg = 0;
    const int _maxProg = 10;

  public:
    enum Color {
      NONE, RED, BLUE, GREEN, YELLOW, MAGENTA, CYAN, ALL
    };
    MultiSensor() : _dht11(DHT11_PIN, DHT11), _ir(IR) {}
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

      _dht11.begin();
      EasyBuzzer.setPin(BUZZER);
      _ir.enableIRIn();
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
        case NONE:
          digitalWrite(RGB_RED, false);
          digitalWrite(RGB_GREEN, false);
          digitalWrite(RGB_BLUE, false);
          break;
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
          digitalWrite(RGB_GREEN, true);
          digitalWrite(RGB_BLUE, false);
          break;
        case CYAN:
          digitalWrite(RGB_RED, false);
          digitalWrite(RGB_GREEN, true);
          digitalWrite(RGB_BLUE, true);
          break;
        case YELLOW:
          digitalWrite(RGB_RED, true);
          digitalWrite(RGB_GREEN, false);
          digitalWrite(RGB_BLUE, true);

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
      digitalWrite(LED_RED, state ? HIGH : LOW);
    }

    void setBlueLED(boolean state) {
      digitalWrite(LED_BLUE, state ? HIGH : LOW);
    }



    int getPoti() {
      return map(analogRead(POTI), 0, 1024, 0, 100);
    }


    int getLDR() {
      return map(analogRead(LDR), 0, 1024, 0, 100);
    }

    /**
       get the temperatur of the LM35
       0 - 1.5V = 0 -150 degree
       0 = 0 , 5 V = 1024 => 1.5V = 307 ;)
    */
    int getLM35() {

      return map(analogRead(LM35),  0, 307, 0, 150);
    }


    void  ircode (decode_results *results)
    {

      long res = results->value;

      for (int i = 0; i < 8 ; i++) {
        //Serial.println(codes[i], HEX);
        if (codes[i] == res) {
          setRGBLed(i) ;
          Serial.print("-> ");
          Serial.print(codeNames[i]);
          Serial.print(" <-");
        }
      }
      Serial.println(res, HEX);
      // Print Code
      //Serial.print(results->value, HEX);
    }
    int curColor = 0;



    void loop(boolean test = false) {
      EasyBuzzer.update();

      if (test) {
        setRedLED(getSwitch1());
        setBlueLED(getSwitch2());
        // Serial.println(_curProg);

        switch (_curProg) {

          case 0:
            //Serial.print("IR: ");
            if (_ir.decode(&_results)) {
              ircode(&_results);
              _ir.resume();
            } else {
              //Serial.println("...nothing...");
            }
            break;
          case 1:
            setRedLED(true);
            Serial.println("Red led on");
            break;
          case 2:
            setBlueLED(true);
            Serial.println("Blue led on");
            break;
          case 4:
            setBlueLED(false);
            setRedLED(false);
            Serial.println("Red and Blue led off");
            break;
          case 5:
            Serial.println("Test the buzzer");
            testBuzzer();
            delay(1000);
            break;

          case 6:
            Serial.print("Poti at: ");
            Serial.print(getPoti());
            Serial.println("%");
            delay(500);
            break;
          case 7:
            Serial.print("LDR: ");
            Serial.print(getLDR());
            Serial.println("%");
            delay(2000);
            break;
          case 8:
            Serial.print("LM35 : ");
            Serial.print(getLM35());
            Serial.println("Â°C");
            delay(2000);
            break;
          case 9: Serial.print("DHT11 : Hum.:");
            Serial.print(getDHT11Humidity());
            Serial.println("% Temp.:");
            Serial.print(getDHT11Temperature());
            Serial.println("Â°C");
            delay(2000);
            break;
          case 10: Serial.println("RGB Light: ");

            setRGBLed(((Color)curColor));
            curColor++;
            if (curColor > 6) {
              curColor = 0;
            }
            delay(2000);
            break;

        }
      }

    }
};




#endif // multi_senosor_h

