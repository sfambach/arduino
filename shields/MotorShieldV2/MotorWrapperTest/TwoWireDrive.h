
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
    int16_t _minSpeed = -200;
    int16_t _maxSpeed = 200;
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
    virtual void setSpeed(int8_t speedLeftPercent, int8_t speedRightPercent) {

      this->_leftSpeed = map(speedLeftPercent, -100, 100, _minSpeed, _maxSpeed);
      this->_rightSpeed  = map(speedRightPercent, -100, 100, _minSpeed, _maxSpeed);

      setDir(TwoWireDrive::Side::LEFT, getDirection(speedLeftPercent));
      setDir(TwoWireDrive::Side::RIGHT, getDirection(speedRightPercent));

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
      DEBUG_PRINT(" [min/max: ");
      DEBUG_PRINT(_minSpeed);
      DEBUG_PRINT(" , ");
      DEBUG_PRINT(_maxSpeed);
      DEBUG_PRINT("]");
      DEBUG_PRINT(" [dir: ");
      DEBUG_PRINT(_leftDirection );
      DEBUG_PRINT(" , ");
      DEBUG_PRINT(_rightDirection);
      DEBUG_PRINT("]\n");

    }
    virtual void init() = 0;
    virtual void setLeftSpeed(int8_t speedPercent) {
      this->_leftSpeed = map(speedPercent, -100, 100, _minSpeed, _maxSpeed);
    }
    virtual void setRightSpeed(int8_t speedPercent) {
      this->_rightSpeed = map(speedPercent, -100, 100, _minSpeed, _maxSpeed);
    }
    //virtual setLeftDirection(Direction dir){this->_leftDirection = dir;}
    //virtual setRightDirection(Direction dir){this->rightDirection= dir;}
    void setMinSpeed(int16_t minSpeed) {
      this->_minSpeed = minSpeed;
    }
    void setMaxSpeed(int16_t maxSpeed) {
      this->_maxSpeed = maxSpeed;
    }

    virtual boolean setSpeed(TwoWireDrive::Side side, int8_t speedPercent) {
      if (side == TwoWireDrive::Side::LEFT) {
        _leftSpeed = map(speedPercent, -100, 100, _minSpeed, _maxSpeed);
        return true;
      } else if (side == TwoWireDrive::Side::RIGHT) {
        _rightSpeed = map(speedPercent, -100, 100, _minSpeed, _maxSpeed);
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

   
};

#endif // TWO_WIRE_DRIVE
