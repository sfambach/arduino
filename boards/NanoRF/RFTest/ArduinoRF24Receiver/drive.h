// class for driving with joystick
// www.fambach.net
// GPL2

#ifndef DRIVE_H
#define DRIVE_H
#include <Wire.h>
#include <Adafruit_MotorShield.h>


class Drive {
  private:
    Adafruit_MotorShield AFMS; // = Adafruit_MotorShield();
    Adafruit_DCMotor* _mLeft = AFMS.getMotor(1);
    Adafruit_DCMotor* _mRight = AFMS.getMotor(2);

    // value to save
    int _dirAF = BACKWARD; // the current driving direction for AF lib
    int _curSpeed = 0;  // the current speed
    int _speedOld = 0;  // old speed value (used?)
    int _center = 512; // center of youstick
    int _steerMax = 54;
    int _speedMax = 254;
    int _factor = 1;
    int _steeringFactor = 54; // masimum of steering 
    bool _speedUp = false;
    bool _dualMotors = false;

  public:
    static const uint8_t MAX_SPEED = 254;

    Drive(bool speedUp = true, bool dualMotors = true, uint8_t mLeft = 1 , uint8_t mRight = 2)
      : _speedUp(speedUp), _dualMotors(dualMotors) {
      AFMS = Adafruit_MotorShield();
      _mLeft = AFMS.getMotor(mLeft);
      _mRight = AFMS.getMotor(mRight);
      setupSteering(speedUp, dualMotors);
    }

    /**
        setup steering
    */
    setupSteering(bool speedUp, bool dualMotors) {

      //      // setup steering size
      //      if (!speedUp && !  dualMotors) {
      //        _steerMax = -_steeringFactor;
      //        Serial.println("Slow down");
      //      } else {
      //        Serial.println("Speed up");
      //        _steerMax = _steeringFactor;
      //      }
      _speedUp = speedUp;
      _dualMotors = dualMotors;
      // calculate max speed
      if (speedUp || dualMotors) {
        _speedMax = MAX_SPEED - _steeringFactor;
      } else {
        _speedMax = MAX_SPEED;
      }

      Serial.print("Max Speed: ");
      Serial.println(_speedMax);
    }

    /**
        use this mothed in setup functions
    */
    void init() {
      Serial.println("init motor");
      AFMS.begin();
      _mLeft->setSpeed(0);
      _mRight->setSpeed(0);
      _mLeft->run(BACKWARD);
      _mRight->run(BACKWARD);
    }


    /**
       Process speed and steering input
       @param dir 0 -1023 , center 512 is zero speed, <512 is backwards
       @param steer 0 -1023 , center 512 straight away,  <512 is left, >512 is right
    */
    void process(int dir, int steer) {
      int deltaLeft = 0, deltaRight = 0;
      _curSpeed = 0;

      // some space to put the finger on the joy
      if (dir < _center + 5  && dir > _center - 5 ) {
        _mLeft->setSpeed(_curSpeed);
        _mRight->setSpeed(_curSpeed);
        return;
      }

      // determine direction
      if (dir < _center) {
        _curSpeed = map (dir, 512, 0, 0, _speedMax);
        _dirAF  = FORWARD;
      } else {
        _curSpeed = map (dir, 0, 1023, 0, _speedMax);
        _dirAF  = BACKWARD;
      }


      // determine delta left and right
      if (steer < _center) { // left turn

        int value = map(steer, 512, 0, 0, _steerMax);

        if (_dualMotors) {
          deltaLeft = -(value/2);
          deltaRight = (value/2);
        } else if (_speedUp) {
          deltaLeft = 0;
          deltaRight = value;
        } else {
          deltaLeft = -value;
          deltaRight = 0;
        }

      } else { // right turn
        int value = map(steer, 512, 1023, 0, _steerMax);
        if (_dualMotors) {
          deltaLeft = (value/2);
          deltaRight = (-value/2);
        } else if (_speedUp) {
          deltaLeft = value;
          deltaRight = 0;
        } else {
          deltaLeft = -0;
          deltaRight = -value;
        }
      }

      _mLeft->run(_dirAF);
      _mRight->run(_dirAF);

      _mLeft->setSpeed(_curSpeed  + deltaLeft);
      _mRight->setSpeed(_curSpeed + deltaRight);

      Serial.print("dir= ");
      Serial.print(String(dir));
      Serial.print(" steer=");
      Serial.print(String(steer));
      Serial.print(" speed=");
      Serial.print(String(_curSpeed));
      Serial.print(" speedLeft =");
      Serial.print(String(_curSpeed  + deltaLeft));
      Serial.print(" speedRight =");
      Serial.print(String(_curSpeed + deltaRight));
      Serial.print(" deltaLeft =");
      Serial.print(String(deltaLeft));
      Serial.print(" deltaRight=");
      Serial.println(String(deltaRight));

    }



};

#endif // #define DRIVE_H

