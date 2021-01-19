#ifndef MotorShieldR3_h
#define MotorShieldR3_h

#include "Arduino.h"

class MotorShieldR3
{
	public:
		MotorShieldR3();
		MotorShieldR3(bool channelSelect);

		void Forward_1W(int pwmSingle);
		void Back_1W(int pwmSingle);
		void Stopped_1W();
		void SetSpeed_1W(int pwmSingle);

		void Forward_2W(int pwmA, int pwmB);
		void Back_2W(int pwmA, int pwmB);
		void RotateLeft_2W(int pwmA, int pwmB);
		void RotateRight_2W(int pwmA, int pwmB);
		void Stopped_2W();
		void SetSpeeds_2W(int pwmA, int pwmB);
		void SetSpeedLeft_2W(int pwmA);
		void SetSpeedRight_2W(int pwmB);

		void Forward_4W(int pwmB);
		void Back_4W(int pwmB);
		void Left_4W();
		void Right_4W();
		void ForwardLeft_4W(int pwmB);
		void ForwardRight_4W(int pwmB);
		void BackLeft_4W(int pwmB);
		void BackRight_4W(int pwmB);
		void Stopped_4W();
		void SetSpeed_4W(int pwmB);
	private:
		bool _channelSelect;
		int	_pinDirA;
		int _pinBrakeA;
		int _pinPwmA;
		int _pinDirB;
		int _pinBrakeB;
		int _pinPwmB;
		int	_pinDirSingle;
		int _pinBrakeSingle;
		int _pinPwmSingle;
		int _pwmA;
		int _pwmB;
		int _pwmSingle;
};

#endif