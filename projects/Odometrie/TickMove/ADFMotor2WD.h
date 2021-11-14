#pragma once

#include <Arduino.h>
#include <Adafruit_MotorShield.h>
#include "TwoWireDrive.h"

class ADFMotor2WD : public TwoWireDrive {

  protected:

    Adafruit_DCMotor * _motorLeft;
    Adafruit_DCMotor * _motorRight;
    Adafruit_MotorShield _afms;
    TwoWire *_theWire;
    uint16_t _freq;


  public:

    ADFMotor2WD(int motorLeftIndex = 1, int motorRightIndex = 2, TwoWire *theWire = &Wire, uint16_t freq = 800):
      _afms(), _theWire(theWire), _freq(freq), TwoWireDrive()
    {
      _motorLeft = _afms.getMotor(motorLeftIndex);
      _motorRight = _afms.getMotor(motorRightIndex);
    }


    virtual void setSpeedBoth(uint8_t speedLeftPercent, uint8_t speedRightPercent) {
      TwoWireDrive::setSpeedBoth(speedLeftPercent, speedRightPercent );

      _motorLeft->setSpeed(abs(_leftSpeed));
      _motorRight->setSpeed(abs(_rightSpeed));

    }


    virtual boolean setSpeed(TwoWireDrive::Side side, uint8_t speed) {
      TwoWireDrive::setSpeed(side, speed );

      if (side == TwoWireDrive::Side::LEFT) {
        _motorLeft->setSpeed(_leftSpeed != 0 ? abs(_leftSpeed) : 0);
        return true;
      } else if (side == TwoWireDrive::Side::RIGHT) {
        _motorRight->setSpeed(_rightSpeed != 0 ? abs(_rightSpeed) : 0);
        return true;
      }
      return false;
    }

    virtual boolean setDir(TwoWireDrive::Side side, TwoWireDrive::Direction dir) {
      TwoWireDrive::setDir(side, dir);
      if ( side == Side::LEFT) {

        _motorLeft->run(TwoWireDrive::Direction::BR);
        delay(100);
        _motorLeft->run(_leftDirection);
        DEBUG_PRINT("Left ");
        DEBUG_PRINT(dir);
        DEBUG_PRINT("\n");
        return true;
      } else if ( side == Side::RIGHT ) {

        _motorRight->run(TwoWireDrive::Direction::BR);
        delay(100);
        _motorRight->run(_rightDirection);
        DEBUG_PRINT("Right ");
        DEBUG_PRINT(dir);
        DEBUG_PRINT("\n");
        return true;
      }
      return;
    }



    virtual void stop() {
      _motorLeft->run(TwoWireDrive::Direction::BR);
      _motorLeft->setSpeed(0);
      _motorRight->run(TwoWireDrive::Direction::BR);
      _motorRight->setSpeed(0);
    }


    void init() {
      //_afms.begin(1000);
     // if (!) {         // create with the default frequency 1.6KHz
       if (!_afms.begin(1000)) {  // OR with a different frequency, say 1KHz
        DEBUG_PRINTLN("Could not find Motor Shield. Check wiring.");
        while (1);
      }
      //      Serial.println("Motor Shield found.");
      _motorLeft->run(TwoWireDrive::Direction::BR);
      _motorRight->run(TwoWireDrive::Direction::BR);
    }
};
