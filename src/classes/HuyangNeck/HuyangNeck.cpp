#include "HuyangNeck.h"
#include <Adafruit_PWMServoDriver.h>

#include "../easing.h"

// Servo Parameters
#define HuyangNeck_SERVOMIN 150	 // This is the 'minimum' pulse length count (out of 4096)
#define HuyangNeck_SERVOMAX 595	 // This is the 'maximum' pulse length count (out of 4096)
#define HuyangNeck_SERVO_FREQ 60 // Analog servos run at ~50 Hz updates

#define pwm_pin_head_rotate (uint8_t)4
#define pwm_pin_head_left (uint8_t)5
#define pwm_pin_head_right (uint8_t)6

HuyangNeck::HuyangNeck(Adafruit_PWMServoDriver *pwm)
{
	_pwm = pwm;
}

void HuyangNeck::rotateServo(uint8_t servo, uint16_t degree)
{
	// Serial.println(F("HuyangNeck rotateServo create pulselength"));

	uint16_t pulselength = map(degree, 0, 180, HuyangNeck_SERVOMIN, HuyangNeck_SERVOMAX); //  Calibrate the positive range (see below)

	// Serial.print(F("rotateServoToDegree Servo: "));
	// Serial.print(servo);
	// Serial.print(F(" to Degree: "));
	// Serial.print(degree);
	// Serial.print(F(" with Pulselength: "));
	// Serial.println(pulselength);

	// Serial.println(F("HuyangNeck rotateServo set PWM"));

	_pwm->setPWM(servo, 0, pulselength);
	// Serial.println(F("done"));
}

double HuyangNeck::easeInAndOut(double start, double current, double target, double percentage)
{
	double result = target;

	if (current != target)
	{
		Serial.print(F("easeInAndOut from "));
		Serial.print(start);
		Serial.print(F(" to "));
		Serial.print(target);
		Serial.print(F(":  current "));
		Serial.print(current);

		auto easingFunction = getEasingFunction(EaseInOutQuad);
		double easeInOut = easingFunction(percentage);

		if (current < target)
		{
			double subTarget = (target - start);

			result = start + (subTarget * easeInOut);

			if (result > target)
			{
				result = target;
			}
		}
		else if (current > target)
		{
			double subTarget = (start - target);

			result = start - (subTarget * easeInOut);

			if (result < target)
			{
				result = target;
			}
		}

		Serial.print(F(":   "));
		Serial.print(result);
	}

	return result;
}

void HuyangNeck::updateNeckPosition()
{
	uint16_t leftDegree = map(targetTiltForward + targetTiltSideways, 0, 100, 65, 10);
	uint16_t rightDegree = map(targetTiltForward - targetTiltSideways, 0, 100, 35, 90);

	leftDegree = min(leftDegree, uint16_t(65));
	leftDegree = max(leftDegree, uint16_t(10));

	rightDegree = min(rightDegree, uint16_t(90));
	rightDegree = max(rightDegree, uint16_t(35));

	rotateServo(pwm_pin_head_left, leftDegree);
	rotateServo(pwm_pin_head_right, rightDegree);
}
void HuyangNeck::tiltSideways(int16_t degree)
{
	degree = min(degree, _maxTiltSideways);
	degree = max(degree, _minTiltSideways);

	targetTiltSideways = degree;
	currentTiltSideways = degree;
}
void HuyangNeck::tiltForward(uint16_t degree)
{
	degree = min(degree, _maxTiltForward);
	degree = max(degree, _minTiltForward);

	targetTiltForward = degree;
	currentTiltForward = degree;
}
void HuyangNeck::rotate(double degree)
{
	degree = min(degree, _maxRotation);
	degree = max(degree, _minRotation);

	_startRotate = _currentRotate;
	targetRotate = degree;
	_rotationPercentage = 0;
}

void HuyangNeck::updateCurrentRotate()
{
	if (_rotationPercentage < 1.0)
	{
		_currentRotate = easeInAndOut(_startRotate, _currentRotate, targetRotate, _rotationPercentage);

		uint16_t rotateDegree = map(_currentRotate, _minRotation, _maxRotation, 0, 110);
		rotateServo(pwm_pin_head_rotate, rotateDegree);

		Serial.print(F("     rotationPercentage: "));
		Serial.println(_rotationPercentage);

		if (targetRotate >= _startRotate)
		{
			_rotationPercentage += 1.0 / ((targetRotate - _startRotate) * 0.5);
		}
		else if (targetRotate < _startRotate) 
		{
			_rotationPercentage += 1.0 / ((_startRotate - targetRotate) * 0.5);
		}

		// _rotationPercentage += 0.02;
	}
}

void HuyangNeck::setup()
{
	rotate(0);
	tiltForward(0);
}

void HuyangNeck::loop()
{
	_currentMillis = millis();
	if (_currentMillis - _previousMillis >= 20)
	{
		_previousMillis = _currentMillis;

		updateNeckPosition();

		updateCurrentRotate();
	}
}