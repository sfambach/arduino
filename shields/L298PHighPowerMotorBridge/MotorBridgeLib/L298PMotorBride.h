#ifndef L298P_MOTOR_BRIDGE
#define L298P_MOTOR_BRIDGE

#include "TwoWireDrive.h"


/**
  Two wire drive
  works with negative speed to drive backward
*/
class L298PMotorBridge : public TwoWireDrive {
  protected:

    uint8_t _pwmLeftPin  = 10;
    uint8_t _dirLeftPin  = 12;
    uint8_t _pwmRightPin = 11;
    uint8_t _dirRightPin = 13;

  public:


    L298PMotorBridge(uint8_t leftPwmPin = 10, uint8_t  leftDirPin = 12, uint8_t  rightPwmPin = 11, uint8_t  rightDirPin = 13):
      _pwmLeftPin(leftPwmPin),
      _dirLeftPin(leftDirPin),
      _pwmRightPin(rightPwmPin),
      _dirRightPin(rightDirPin)
    {

      Serial.print("Constructor: ");
      Serial.print( _pwmLeftPin); Serial.print(",");
      Serial.print(_dirLeftPin); Serial.print(",");
      Serial.print(_pwmRightPin); Serial.print(",");
      Serial.print(_dirRightPin); Serial.print(",");


    };

    virtual setSpeed(int8_t speedLeftPercent, uint8_t speedRightPercent) {
      TwoWireDrive::setSpeed(speedLeftPercent, speedRightPercent );
      
      if (_leftSpeed < 0 ) { // backward
        digitalWrite(_dirLeftPin, _backward );
      } else {
        digitalWrite(_dirLeftPin, _foreward );
      }

      if (_rightSpeed < 0 ) { // backward
        digitalWrite(_dirLeftPin, _backward );
      } else {
        digitalWrite(_dirLeftPin, _foreward );
      }

      analogWrite(_pwmLeftPin, abs( _leftSpeed));
      analogWrite(_pwmRightPin, abs(_rightSpeed));
    }
    virtual setLeftSpeed(int8_t speedPercent) {
      this->_leftSpeed = map(speedPercent, -100, 100, _minSpeed, _maxSpeed);
    }
    
    virtual setRightSpeed(int8_t speedPercent) {
      this->_rightSpeed = map(speedPercent, -100, 100, _minSpeed, _maxSpeed);
    }

    void setMinSpeed(int8_t minSpeed) {
      this->_minSpeed = minSpeed;
    }
    
    void setMaxSpeed(int8_t maxSpeed) {
      this->_maxSpeed = maxSpeed;
    }

    void stop() {
         this->_leftSpeed = 0;
         this->_rightSpeed = 0;
         analogWrite(_pwmLeftPin, _leftSpeed);
         analogWrite(_pwmRightPin, _rightSpeed);
    }
    
    void init() {
      //Serial.println("Start init Motor pins");
      // init motor pins
      pinMode( _pwmLeftPin, OUTPUT);
      pinMode( _dirLeftPin, OUTPUT);
      pinMode( _pwmRightPin, OUTPUT);
      pinMode( _dirRightPin, OUTPUT);
     // Serial.println("End init Motor pins");
      stop();
    }


    //virtual setDirection(Direction leftDirection, Direction rightDirection)= 0;
    //virtual setLeftDirection(Direction dir){this->_leftDirection = dir;}
    //virtual setRightDirection(Direction dir){this->rightDirection= dir;}



};

#endif // L298P_MOTOR_BRIDGE
