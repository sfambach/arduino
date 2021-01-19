#include "Arduino.h"
#include "MotorShieldR3.h"

MotorShieldR3::MotorShieldR3()
{
	//Channel A
	pinMode(12, OUTPUT);
	_pinDirA = 12;
	pinMode(9, OUTPUT);
	_pinBrakeA = 9;
	pinMode(3, OUTPUT);
	_pinPwmA = 3;
	//Channel B
	pinMode(13, OUTPUT);
	_pinDirB = 13;
	pinMode(8, OUTPUT);
	_pinBrakeB = 8;
	pinMode(11, OUTPUT);
	_pinPwmB = 11;
}

MotorShieldR3::MotorShieldR3(bool channelSelect)
{
	_channelSelect = channelSelect;
	if(_channelSelect){//Channel A
		pinMode(12, OUTPUT);
		_pinDirSingle = 12;
		pinMode(9, OUTPUT);
		_pinBrakeSingle = 9;
		pinMode(3, OUTPUT);
		_pinPwmSingle = 3;
	}
	else{//Channel B
		pinMode(13, OUTPUT);
		_pinDirSingle = 13;
		pinMode(8, OUTPUT);
		_pinBrakeSingle = 8;
		pinMode(11, OUTPUT);
		_pinPwmSingle = 11;	
	}
}
//-----------------Single Back Motor-----------------------
void MotorShieldR3::Forward_1W(int pwmSingle){
	_pwmSingle = pwmSingle;
	digitalWrite(_pinDirSingle,HIGH);
	digitalWrite(_pinBrakeSingle,LOW);
	analogWrite(_pinPwmSingle,_pwmSingle);
}

void MotorShieldR3::Back_1W(int pwmSingle){
	_pwmSingle = pwmSingle;
	digitalWrite(_pinDirSingle,LOW);
	digitalWrite(_pinBrakeSingle,HIGH);
	analogWrite(_pinPwmSingle,_pwmSingle);
}

void MotorShieldR3::Stopped_1W(){
	_pwmSingle = 0;
	digitalWrite(_pinDirSingle,LOW);
	digitalWrite(_pinBrakeSingle,LOW);
	analogWrite(_pinPwmSingle,_pwmSingle);
}

void MotorShieldR3::SetSpeed_1W(int pwmSingle){
	_pwmSingle = pwmSingle;
	analogWrite(_pinPwmSingle,_pwmSingle);
}
//-----------------Independant Left and Right Motors-----------------------
void MotorShieldR3::Forward_2W(int pwmA, int pwmB){
	_pwmA = pwmA;
	_pwmB = pwmB;
	digitalWrite(_pinDirA,HIGH);
	digitalWrite(_pinBrakeA,LOW);
	analogWrite(_pinPwmA,_pwmA);
	digitalWrite(_pinDirB,HIGH);
	digitalWrite(_pinBrakeB,LOW);
	analogWrite(_pinPwmB,_pwmB);
}
void MotorShieldR3::Back_2W(int pwmA, int pwmB){
	_pwmA = pwmA;
	_pwmB = pwmB;
	digitalWrite(_pinDirA,LOW);
	digitalWrite(_pinBrakeA,LOW);
	analogWrite(_pinPwmA,_pwmA);
	digitalWrite(_pinDirB,LOW);
	digitalWrite(_pinBrakeB,LOW);
	analogWrite(_pinPwmB,_pwmB);
}
void MotorShieldR3::RotateLeft_2W(int pwmA, int pwmB){
	_pwmA = pwmA;
	_pwmB = pwmB;
	digitalWrite(_pinDirA,LOW);
	digitalWrite(_pinBrakeA,LOW);
	analogWrite(_pinPwmA,_pwmA);
	digitalWrite(_pinDirB,HIGH);
	digitalWrite(_pinBrakeB,LOW);
	analogWrite(_pinPwmB,_pwmB);
}
void MotorShieldR3::RotateRight_2W(int pwmA, int pwmB){
	_pwmA = pwmA;
	_pwmB = pwmB;
	digitalWrite(_pinDirA,HIGH);
	digitalWrite(_pinBrakeA,LOW);
	analogWrite(_pinPwmA,_pwmA);
	digitalWrite(_pinDirB,LOW);
	digitalWrite(_pinBrakeB,LOW);
	analogWrite(_pinPwmB,_pwmB);
}
void MotorShieldR3::Stopped_2W(){
	_pwmA = 0;
	_pwmB = 0;
	digitalWrite(_pinDirA,LOW);
	digitalWrite(_pinBrakeA,HIGH);
	analogWrite(_pinPwmA,_pwmA);
	digitalWrite(_pinDirB,LOW);
	digitalWrite(_pinBrakeB,HIGH);
	analogWrite(_pinPwmB,_pwmB);
}
void MotorShieldR3::SetSpeeds_2W(int pwmA, int pwmB){
	_pwmA = pwmA;
	_pwmB = pwmB;
	analogWrite(_pinPwmA,_pwmA);
	analogWrite(_pinPwmB,_pwmB);
}
void MotorShieldR3::SetSpeedLeft_2W(int pwmA){
	_pwmA = pwmA;
	analogWrite(_pinPwmA,_pwmA);
}
void MotorShieldR3::SetSpeedRight_2W(int pwmB){
	_pwmB = pwmB;
	analogWrite(_pinPwmB,_pwmB);
}
//-----------------Back Motor and Front Motor for Steering-----------------------
void MotorShieldR3::Forward_4W(int pwmB){
	_pwmB = pwmB;
	digitalWrite(_pinDirA,LOW);
	digitalWrite(_pinBrakeA,HIGH);
	digitalWrite(_pinPwmA,LOW);
	digitalWrite(_pinDirB,HIGH);
	digitalWrite(_pinBrakeB,LOW);
	analogWrite(_pinPwmB,_pwmB);
}
void MotorShieldR3::Back_4W(int pwmB){
	_pwmB = pwmB;
	digitalWrite(_pinDirA,LOW);
	digitalWrite(_pinBrakeA,HIGH);
	digitalWrite(_pinPwmA,LOW);
	digitalWrite(_pinDirB,LOW);
	digitalWrite(_pinBrakeB,LOW);
	analogWrite(_pinPwmB,_pwmB);
}
void MotorShieldR3::Left_4W(){
	_pwmB = 0;
	digitalWrite(_pinDirA,HIGH);
	digitalWrite(_pinBrakeA,LOW);
	digitalWrite(_pinPwmA,HIGH);
	digitalWrite(_pinDirB,LOW);
	digitalWrite(_pinBrakeB,HIGH);
	analogWrite(_pinPwmB,_pwmB);
}
void MotorShieldR3::Right_4W(){
	_pwmB = 0;
	digitalWrite(_pinDirA,LOW);
	digitalWrite(_pinBrakeA,LOW);
	digitalWrite(_pinPwmA,HIGH);
	digitalWrite(_pinDirB,LOW);
	digitalWrite(_pinBrakeB,HIGH);
	analogWrite(_pinPwmB,_pwmB);
}
void MotorShieldR3::ForwardLeft_4W(int pwmB){
	_pwmB = pwmB;
    digitalWrite(_pinDirA,HIGH);
	digitalWrite(_pinBrakeA,LOW);
	digitalWrite(_pinPwmA,HIGH);
	digitalWrite(_pinDirB,HIGH);
	digitalWrite(_pinBrakeB,LOW);
	analogWrite(_pinPwmB,_pwmB);
}
void MotorShieldR3::ForwardRight_4W(int pwmB){
	_pwmB = pwmB;
	digitalWrite(_pinDirA,LOW);
	digitalWrite(_pinBrakeA,LOW);
	digitalWrite(_pinPwmA,HIGH);
	digitalWrite(_pinDirB,HIGH);
	digitalWrite(_pinBrakeB,LOW);
	analogWrite(_pinPwmB,_pwmB);
}
void MotorShieldR3::BackLeft_4W(int pwmB){
	_pwmB = pwmB;
	digitalWrite(_pinDirA,HIGH);
	digitalWrite(_pinBrakeA,LOW);
	digitalWrite(_pinPwmA,HIGH);
	digitalWrite(_pinDirB,LOW);
	digitalWrite(_pinBrakeB,LOW);
	analogWrite(_pinPwmB,_pwmB);
}
void MotorShieldR3::BackRight_4W(int pwmB){
	_pwmB = pwmB;
	digitalWrite(_pinDirA,LOW);
	digitalWrite(_pinBrakeA,LOW);
	digitalWrite(_pinPwmA,HIGH);
	digitalWrite(_pinDirB,LOW);
	digitalWrite(_pinBrakeB,LOW);
	analogWrite(_pinPwmB,_pwmB);
}
void MotorShieldR3::Stopped_4W(){
	_pwmB = 0;
	digitalWrite(_pinDirA,LOW);
	digitalWrite(_pinBrakeA,HIGH);
	digitalWrite(_pinPwmA,LOW);
	digitalWrite(_pinDirB,LOW);
	digitalWrite(_pinBrakeB,HIGH);
	analogWrite(_pinPwmB,_pwmB);
}
void MotorShieldR3::SetSpeed_4W(int pwmB){
	_pwmB = pwmB;
	analogWrite(_pinPwmB,_pwmB);
}