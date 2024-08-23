#include "HuyangNeck.h"
#include <Adafruit_PWMServoDriver.h>

HuyangNeck::HuyangNeck(Adafruit_PWMServoDriver *pwm)
{
	_pwm = pwm;
}

void HuyangNeck::rotateServo(uint8_t servo, double degree)
{
	// Serial.println("HuyangNeck rotateServo create pulselength");

	uint16_t pulselength = map(degree, 0, 180, HuyangNeck_SERVOMIN, HuyangNeck_SERVOMAX); //  Calibrate the positive range (see below)

	// Serial.print("rotateServoToDegree Servo: ");
	// Serial.print(servo);
	// Serial.print(" to Degree: ");
	// Serial.print(degree);
	// Serial.print(" with Pulselength: ");
	// Serial.println(pulselength);

	// Serial.println("HuyangNeck rotateServo set PWM");

	_pwm->setPWM(servo, 0, pulselength);
	// Serial.println("done");
}

double HuyangNeck::easeInOutQuad(double t)
{
	return t < 0.5 ? 2 * t * t : t * (4 - 2 * t) - 1;
}

double HuyangNeck::easeInAndOut(double start, double current, double target, double percentage)
{
	double result = target;

	if (percentage > 1.0)
	{
		percentage = 1.0;
	}

	if (current != target)
	{
		// Serial.print("easeInAndOut from ");
		// Serial.print(start);
		// Serial.print(" to ");
		// Serial.print(target);
		// Serial.print(":  current ");
		// Serial.print(current);

		double easeInOut = easeInOutQuad(percentage);

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

		// Serial.print(":   ");
		// Serial.print(result);
	}

	return result;
}

void HuyangNeck::updateNeckPosition()
{
	if (_currentTiltForward != targetTiltForward)
	{
		double tiltForwardPercentage = (_currentMillis - _tiltForwardStartMillis) / _tiltForwardDuration;
		_currentTiltForward = easeInAndOut(_startTiltForward, _currentTiltForward, targetTiltForward, tiltForwardPercentage);
	}

	if (_tiltSidewaysPercentage < 1.0)
	{
		_currentTiltSideways = easeInAndOut(_startTiltSideways, _currentTiltSideways, targetTiltSideways, _tiltSidewaysPercentage);
		_tiltSidewaysPercentage += 0.06;
	}

	uint16_t leftDegree = map(_currentTiltForward + _currentTiltSideways, 0, 200, 65, 10);
	uint16_t rightDegree = map(_currentTiltForward - _currentTiltSideways, 0, 200, 35, 90);
	uint16_t neckDegree = map(_currentTiltForward, 0, 200, 100, 0);

	leftDegree = constrain(leftDegree, uint16_t(10), uint16_t(65));
	rightDegree = constrain(rightDegree, uint16_t(35), uint16_t(90));
	neckDegree = constrain(neckDegree, uint16_t(0), uint16_t(100));

	rotateServo(pwm_pin_head_left, leftDegree);
	rotateServo(pwm_pin_head_right, rightDegree);
	rotateServo(pwm_pin_head_neck, neckDegree);
}

void HuyangNeck::setup()
{
	rotateHead(0);
	tiltNeckForward(0);
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

	if (automatic == true)
	{
		doRandomRotate();

		doRandomTiltForward();
	}
}