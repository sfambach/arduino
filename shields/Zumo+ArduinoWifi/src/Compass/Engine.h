#ifndef _ZUMO_ENGINE__
#define _ZUMO_ENGINE__

/** simple engine control class for the zumo arduino "shield"
* Free to use no warranty ;) 
* License: GPL3 
* Created by Stefan Fambach visit www.fambach.net id you want.
*/

#include<Arduino.h>
#include "Credentials.h"


class Engine {
	public: 
    static const uint8_t FOREWARD = LOW;
    static const uint8_t BACKWARD = HIGH;
    static const uint8_t RIGHT = 2;
    static const uint8_t LEFT = 1;
    static const uint8_t STOP = 0;
    const int freq = 10000;
    const int resolution = 8;
    
	private:

	uint8_t _leftPWMPin = 11;
	uint8_t _leftDirPin = 9;
	uint8_t _rightPWMPin = 10;
	uint8_t _rightDirPin = 8;

  uint8_t _leftSpeed = STOP;
  uint8_t _rightSpeed = STOP;

  uint8_t _leftDir = FOREWARD;
  uint8_t _rightDir = FOREWARD;

  
	
	public:
	
	Engine(){}
	
	Engine(uint8_t leftPWMPin, uint8_t leftDirPin, uint8_t rigthPWMPin, uint8_t rightDirPin)
	: _leftPWMPin(leftPWMPin), _leftDirPin(leftDirPin), _rightPWMPin(rigthPWMPin), _rightDirPin(rightDirPin)
	{}
	
	void init(){

    _leftDir = FOREWARD;
    _rightDir = FOREWARD;
    _leftSpeed = STOP;
    _rightSpeed = STOP;
    
		pinMode(_leftPWMPin,OUTPUT);
		pinMode(_leftDirPin,OUTPUT);
		pinMode(_rightPWMPin,OUTPUT);
		pinMode(_rightDirPin,OUTPUT);
		
		digitalWrite(_leftPWMPin, LOW);
		digitalWrite(_leftDirPin, LOW);
		digitalWrite(_rightPWMPin, LOW);
		digitalWrite(_rightDirPin, LOW);

#ifdef D1R32
    ledcSetup(LEFT, freq, resolution);
    ledcAttachPin(_leftPWMPin, LEFT);
    ledcSetup(RIGHT, freq, resolution);
    ledcAttachPin(_rightPWMPin, RIGHT);
#endif
    
	}
	
	/** set direction of single engine */
	void setDirection(uint8_t engine, uint8_t dir){
		switch(engine){
			case (LEFT): digitalWrite(_leftDirPin, dir);break;
			case (RIGHT): digitalWrite(_rightDirPin, dir);break;
		};
	}
		
	/** set the direction of both engines */
	void setDirection(uint8_t dir){
		digitalWrite(_leftDirPin, dir);
		digitalWrite(_rightDirPin, dir);
	}

	/** set speed of single engine */
	void setSpeed(uint8_t engine, uint8_t speed){
		switch(engine){
			case (LEFT): 
			  analogOut(_leftPWMPin, map(speed, 0,255, 0, 1024 ));
        _leftSpeed=speed;
			  break;
			case (RIGHT): 
			  analogOut(_rightPWMPin, map(speed, 0,255, 0, 1024 ));
        _rightSpeed= speed;
			  break;
		};
	}
	
	/** set the speed of both engines */	
	void setSpeed(uint8_t speed){
    _leftSpeed = speed;
    _rightSpeed = speed;
		analogOut(_leftPWMPin, speed);
		analogOut(_rightPWMPin, speed);
	}

  void analogOut(uint8_t pin, uint8_t value){
#if defined(D1R32)
    
    if(pin ==  _leftPWMPin) {
      ledcWrite(LEFT, value);
    }else if(pin ==  _rightPWMPin){
      ledcWrite(RIGHT, value); 
    };
#else 
    analogWrite(pin, value);
#endif
 }
	
	/** stop both engines */
	void stop(){
    setSpeed(STOP);
	}
	
};

#endif // _ZUMO_ENGINE__
