/** class to control a npod for example a hexapod
	This class works with mutiple of 2 legs and
	was tested with a hexapod.
	Each leg in this version has two servos one for up down
	and one for forward backward


  http://www.fambach.net
  GPL v2
*/

#ifndef xpod_h
#define xpod_h

// Servo things ...
#include "Adafruit_PWMServoDriver.h"

class XPod {

  public:

    const bool LEFT = true;
    const bool RIGHT = false;
    enum Mode {
      NONE = 0,
      LINE_DANCE,
      STEP_DOWN,
      DUCK,
      GROW,
      ATTACK,
      SWING_RIGHT,
      SWING_LEFT
    };

    XPod(uint8_t legCount): _legCount(legCount), _servos(), _mode(NONE) {

    }

    void setup() {
      _servos.begin();
      _servos.setPWMFreq(60);
    }

    void loop() {

      if (!checkDelay()) {
        return;
      }

      setMode(false, _mode);
    }


    void setMode(bool initial, Mode mode) {
      _mode = mode;

      switch (_mode) {
        case LINE_DANCE: lineDance(initial); break;
        case STEP_DOWN:  lineDance(initial); break;
        case DUCK:  duck(); break;
        case GROW:  grow(); break;
        case ATTACK: attack(initial); break;
        case SWING_RIGHT: swing(RIGHT); break;
        case SWING_LEFT: swing(LEFT); break;
        default: // do nothing ... ;
          centerAll();
          break;
      }
    }



    void legY(int legId, uint8_t percent) {
      _servos.setPin(legId, map(percent, 0, 100, MIN_PULSE, MAX_PULSE));
      startDelay(_defaultDelay);
    }
    void legX(int legId, uint8_t percent) {
      _servos.setPin(legId + _legCount, map(percent, 0, 100, MIN_PULSE, MAX_PULSE));
      startDelay(_defaultDelay);
    }

    void x(uint8_t pos){
      for (int i = 0; i <  _legCount; i ++) {
        legX(i, pos);
      }
    }

    void y(uint8_t pos){
      for (int i = 0; i <  _legCount; i ++) {
        legY(i, pos);
      }
    }

    void xCenter() {
      x(_xCenter);
    }
    void yCenter() {
      y(_yCenter);
    }
    void centerAll() {
      xCenter();
      yCenter();
    }

    void moveforward();
    void movePackward();
    void straveLeft();
    void straveRight();
    void turnLeft();
    void turnRight() {

      int startLeft = 0;
      int startRight = _legCount / 2;

      for (int i = 0 ; i < _legCount / 2; i++) {

        legY(startLeft, 100);
        delay(100);
        legX(startLeft, 100);
        delay(100);
        legY(startLeft, 50);
        delay(100);

        legY(startRight, 0);
        delay(100);
        legX(startRight, 0);
        delay(100);
        legY(startRight, 50);
        delay(100);

        startLeft++;
        startRight++;
      }

      // move all to rotate
      for ( int i = 0; i < _legCount; i++) {
        legX(i, 50);
      }

    }


    void duck() {
      y(20);
    }
    void grow() {
      y(90);
    }


    void swing(bool dir) {
        
      if(dir == RIGHT){
        x(10);
      }else {
        x(80);
      }
    }

    void centerLegs() {
      for (int i = 0; i < _legCount; i++) {
        legY(i, 50);
        legX(i, 50);
      }
      delay(300);
    }


    void lineDance(bool initial) {


      if (initial) {
        centerAll();
        _step = 0;
        _subStep = 0;

      }

      switch (_subStep) {
        case 0:
          if (_mode == STEP_DOWN) {
            legY(_step, 90);
          } else {
            legY(_step, 20);
          }
          _subStep++;
          break;
        case 1:
          legY(_step, _xCenter);
          _subStep = 0;
          _step ++;
          break;
      }
 
      if (_step >= _legCount) {
        _step = 0;
      }
    }


     void attack(bool initial) {


      if (initial) {
        centerAll();
        _step = 0;
        _subStep = 0;
      }

      switch (_step) {
        case 0:
        legY(5,_yCenter -20);
        legY(2,_yCenter -20);
        break;
        case 1:
        legX(5,_xCenter +40);
        legX(2,_xCenter -40);
        break;
        case 2:
        legY(5,_yCenter);
        legY(2,_yCenter);
        legY(4,_yCenter +20);
        legY(3,_yCenter +20);
        break;
        case 3:
        legX(4,_xCenter -40);
        legX(3,_xCenter +40);
        break;
        case 4:
        legY(4,10);
        legY(3,10);
        legY(5,90);
        legY(2,90);
        legY(0,20);
        legY(1,20);
        case 5:
        legY(0,80);
        
        case 6:
        legY(0,20);
           
        break;


        
        case 10:
        centerAll();
        break;
      }
      _step ++;
      if (_step > 10) {
        _step = 0;
      }
    }
    
  protected:
    uint8_t _legCount;
    uint8_t _positions[];
    uint8_t _curPositions[];
    int _defaultDelay = 1000;
    uint8_t _xCenter = 50;
    uint8_t _yCenter = 50;
    Mode _mode = Mode::NONE;
    uint8_t _step = 0;
    uint8_t _subStep = 0;

    long _refTime;
    int _curDelay;

    Adafruit_PWMServoDriver _servos;


    const int MIN_PULSE = 100;// this is the 'minimum' pulse length count (out of 4096)
    const int MAX_PULSE = 580; // this is the 'maximum' pulse length count (out of 4096)

    void startDelay(long del) {
      _refTime = millis();
      _curDelay = del;
    }

    bool checkDelay() {
      return (millis() - _refTime) > _curDelay;
    }

};


#endif // xpod_h
