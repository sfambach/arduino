
#ifndef TWO_WIRE_DRIVE
#define TWO_WIRE_DRIVE


/**
  Two wire drive
  works with negative speed to drive backward
*/
class TwoWireDrive {
  protected:
    int8_t _minSpeed = -255;
    int8_t _maxSpeed = 255;
    int8_t _leftSpeed = 0;
    int8_t _rightSpeed = 0;
    int8_t minPercentSpeed = 10;
    //Direction _leftDirection = STOP;
    //Direction _rightDirection = STOP;
    int _foreward = HIGH;
    int _backward = LOW;



  public:

    //virtual setDirection(Direction leftDirection, Direction rightDirection)= 0;
    virtual setSpeed(int8_t speedLeftPercent, uint8_t speedRightPercent) {

      if (speedLeftPercent == 0) {
        this->_leftSpeed = 0;
      }
      else {
        this->_leftSpeed = map(speedLeftPercent, -100, 100, _minSpeed, _maxSpeed);
      }

      if (speedRightPercent == 0) {
        this->_rightSpeed = 0;
      }
      else {
        this->_rightSpeed = map(speedRightPercent, -100, 100, _minSpeed, _maxSpeed);
      }
    
    }
    virtual void init() = 0;
    virtual setLeftSpeed(int8_t speedPercent) {
      this->_leftSpeed = map(speedPercent, -100, 100, _minSpeed, _maxSpeed);
    }
    virtual setRightSpeed(int8_t speedPercent) {
      this->_rightSpeed = map(speedPercent, -100, 100, _minSpeed, _maxSpeed);
    }
    //virtual setLeftDirection(Direction dir){this->_leftDirection = dir;}
    //virtual setRightDirection(Direction dir){this->rightDirection= dir;}
    void setMinSpeed(int8_t minSpeed) {
      this->_minSpeed = minSpeed;
    }
    void setMaxSpeed(int8_t maxSpeed) {
      this->_maxSpeed = maxSpeed;
    }

    void stop() {
      setSpeed(0, 0);
    }

};

#endif // TWO_WIRE_DRIVE
