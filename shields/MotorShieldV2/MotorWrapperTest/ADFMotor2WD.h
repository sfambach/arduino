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


    virtual void setSpeed(int8_t speedLeftPercent, uint8_t speedRightPercent) {
      TwoWireDrive::setSpeed(speedLeftPercent, speedRightPercent );

      _motorLeft->setSpeed(abs(_leftSpeed));
      _motorRight->setSpeed(abs(_rightSpeed));

    }


    virtual boolean setSpeed(TwoWireDrive::Side side, int8_t speed) {
      TwoWireDrive::setSpeed(side, speed );

      if (side == TwoWireDrive::Side::LEFT) {
        _motorLeft->setSpeed(abs(_leftSpeed));
        return true;
      } else if (side == TwoWireDrive::Side::RIGHT) {
        _motorRight->setSpeed(abs(_rightSpeed));
        return true;
      }
      return false;
    }

    virtual boolean setDir(TwoWireDrive::Side side, TwoWireDrive::Direction dir) {

      if ( side == Side::LEFT && TwoWireDrive::setDir(side, dir)) {
        _motorLeft->run(TwoWireDrive::Direction::BR);
        delay(100);
        _motorLeft->run(_leftDirection);
        DEBUG_PRINT("Left ");
        DEBUG_PRINT(dir);
        DEBUG_PRINT("\n");
        return true;
      } else if ( side == Side::RIGHT && TwoWireDrive::setDir(side, dir)) {
        {
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
    }



    virtual void stop() {
      _motorLeft->run(TwoWireDrive::Direction::BR);
      _motorLeft->setSpeed(0);
      _motorRight->run(TwoWireDrive::Direction::BR);
      _motorRight->setSpeed(0);
    }


    void init() {
      _afms.begin(1000);
      //      if (!) {         // create with the default frequency 1.6KHz
      //        // if (!AFMS.begin(1000)) {  // OR with a different frequency, say 1KHz
      //        Serial.println("Could not find Motor Shield. Check wiring.");
      //        while (1);
      //      }
      //      Serial.println("Motor Shield found.");

      // Set the speed to start, from 0 (off) to 255 (max speed)
      _motorLeft->setSpeed(150);
      _motorLeft->run(FORWARD);
      // turn on motor
      _motorLeft->run(RELEASE);
      _leftDirection = TwoWireDrive::Direction::RL;

      // Set the speed to start, from 0 (off) to 255 (max speed)
      _motorRight->setSpeed(150);
      _motorRight->run(FORWARD);
      // turn on motor
      _motorRight->run(RELEASE);
      _rightDirection = TwoWireDrive::Direction::RL;

    }
};
