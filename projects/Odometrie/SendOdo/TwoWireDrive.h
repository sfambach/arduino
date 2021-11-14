
#ifndef TWO_WIRE_DRIVE
#define TWO_WIRE_DRIVE

#define DEBUG
#ifdef DEBUG
#define DEBUG_PRINT(x) Serial.print (x)
#define DEBUG_PRINTLN(x) Serial.println (x)
#else
#define DEBUG_PRINT(x)
#define DEBUG_PRINTLN(x)
#endif





/**
  Two wire drive
  works with negative speed to drive backward
*/
class TwoWireDrive {
  protected:
    int16_t _speedLeftMin = -200;
    int16_t _speedLeftMax = 200;
    int16_t _speedRightMin = -200;
    int16_t _speedRightMax = 20;

    int16_t _leftSpeed = 0;
    int16_t _rightSpeed = 0;
    int8_t minPercentSpeed = 10;
    //Direction _leftDirection = ST;
    //Direction _rightDirection = ST;
    int _foreward = HIGH;
    int _backward = LOW;
    uint8_t _leftDirection = Direction::FW;
    uint8_t _rightDirection = Direction::FW;

  public:

    enum Side {
      LEFT,
      RIGHT
    };

    enum Direction {
      FW = 1,
      BW = 2,
      BR = 3,
      RL = 4
    };

    TwoWireDrive::Direction getDirection(int16_t speed) {
      if (speed == 0 ) {
        return Direction::BR;
      } else if (speed < 0) {
        return Direction::BW;
      } else {
        Direction::FW;
      }
    }

    //virtual setDirection(TwoWireDrive::Direction leftDirection, TwoWireDrive::Direction rightDirection)= 0;
    virtual void setSpeedBoth(uint8_t speedLeftPercent, uint8_t speedRightPercent) {

      this->_leftSpeed = speedLeftPercent; // map(speedLeftPercent, -100, 100, _speedLeftMin, _speedLeftMax);
      this->_rightSpeed  = speedRightPercent; //map(speedRightPercent, -100, 100, _speedRightMin, _speedRightMax);

//      setDir(TwoWireDrive::Side::LEFT, getDirection(speedLeftPercent));
//      setDir(TwoWireDrive::Side::RIGHT, getDirection(speedRightPercent));

      DEBUG_PRINT("-> [%: ");
      DEBUG_PRINT(speedLeftPercent);
      DEBUG_PRINT(" , ");
      DEBUG_PRINT(speedRightPercent);
      DEBUG_PRINT("]");
      DEBUG_PRINT(" [int: ");
      DEBUG_PRINT(this->_leftSpeed);
      DEBUG_PRINT(" , ");
      DEBUG_PRINT(this->_rightSpeed);
      DEBUG_PRINT("]");
      DEBUG_PRINT(" [ABS: ");
      DEBUG_PRINT(abs(this->_leftSpeed));
      DEBUG_PRINT(" , ");
      DEBUG_PRINT(abs(this->_rightSpeed));
      DEBUG_PRINT("]");
//      DEBUG_PRINT(" [min/max: ");
//      DEBUG_PRINT(_minSpeed);
//      DEBUG_PRINT(" , ");
//      DEBUG_PRINT(_maxSpeed);
//      DEBUG_PRINT("]");
      DEBUG_PRINT(" [dir: ");
      DEBUG_PRINT(_leftDirection );
      DEBUG_PRINT(" , ");
      DEBUG_PRINT(_rightDirection);
      DEBUG_PRINT("]\n");

    }
    virtual void init() = 0;

    virtual boolean setSpeed(TwoWireDrive::Side side, uint8_t speedPercent) {
      if (side == TwoWireDrive::Side::LEFT) {
//          if(speedPercent = 0){
//            _leftSpeed = 0;    
//            return true;
//          }
          
        
        _leftSpeed = speedPercent; //map(speedPercent, -100, 100, _speedLeftMin, _speedLeftMax);
        return true;
      } else if (side == TwoWireDrive::Side::RIGHT) {

//        if(speedPercent = 0){
//            _rightSpeed =0;    
//            return true;
//          }
//        
        _rightSpeed = speedPercent; // map(speedPercent, -100, 100, _speedRightMin, _speedRightMax);
        return true;
      }
      return false;
    }

    virtual boolean setDirBoth(TwoWireDrive::Direction left, TwoWireDrive::Direction right){
      return 
      setDir(TwoWireDrive::Side::LEFT , left)&&
      setDir(TwoWireDrive::Side::RIGHT, right);
    }


    virtual boolean setDir(TwoWireDrive::Side side, TwoWireDrive::Direction dir) {
      
      if (side == TwoWireDrive::Side::LEFT && _leftDirection != dir) {
        DEBUG_PRINT("Dir ");
        DEBUG_PRINT(_leftDirection);
        DEBUG_PRINT("/");
        DEBUG_PRINTLN(dir);
        _leftDirection = dir;
        return true;
      } else if (side == TwoWireDrive::Side::RIGHT && _rightDirection != dir) {
        _rightDirection = dir;
        return true;
      }
      return false;
    }

    virtual void stop() {
      setSpeed(0, 0);
    }

    int16_t getSpeedMin(TwoWireDrive::Side side){return side == TwoWireDrive::Side::LEFT?_speedLeftMin:_speedRightMin; }
    int16_t getSpeedMax(TwoWireDrive::Side side){return side == TwoWireDrive::Side::LEFT?_speedLeftMax:_speedRightMax; }

    void setSpeedMin(TwoWireDrive::Side side, int16_t s){side == TwoWireDrive::Side::LEFT?_speedLeftMin = s:_speedRightMin = s;}
    void setSpeedMax(TwoWireDrive::Side side, int16_t s){side == TwoWireDrive::Side::LEFT?_speedLeftMax = s:_speedRightMax = s; }

    int16_t getSpeedLeftMin(){return _speedLeftMin; }
    int16_t getSpeedRightMin(){return _speedRightMin; }
    int16_t getSpeedLeftMax(){return _speedLeftMax; }
    int16_t getSpeedRightMax(){return _speedRightMax; }

    void setSpeedLeftMin(int16_t s) {return _speedLeftMin; }
    void setSpeedRightMin(int16_t s){return _speedRightMin; }
    void setSpeedLeftMax(int16_t s) {return _speedLeftMax; }
    void setSpeedRightMax(int16_t s){return _speedRightMax; }
      

   
};

#endif // TWO_WIRE_DRIVE
