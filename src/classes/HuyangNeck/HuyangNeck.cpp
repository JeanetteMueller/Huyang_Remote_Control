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
#define pwm_pin_head_neck (uint8_t)7

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

	uint16_t leftDegree = map(_currentTiltForward + _currentTiltSideways, 0, 100, 65, 10);
	uint16_t rightDegree = map(_currentTiltForward - _currentTiltSideways, 0, 100, 35, 90);
	uint16_t neckDegree = map(_currentTiltForward, 0, 90, 0, 100);


	leftDegree = constrain(leftDegree, uint16_t(10), uint16_t(65));
	rightDegree = constrain(rightDegree, uint16_t(35), uint16_t(90));
	neckDegree = constrain(neckDegree, uint16_t(0), uint16_t(100));

	rotateServo(pwm_pin_head_left, leftDegree);
	rotateServo(pwm_pin_head_right, rightDegree);
	rotateServo(pwm_pin_head_neck, neckDegree);
}
void HuyangNeck::tiltSideways(double degree)
{
	degree = min(degree, _maxTiltSideways);
	degree = max(degree, _minTiltSideways);

	if (targetTiltSideways != degree)
	{
		_startTiltSideways = _currentTiltSideways;
		targetTiltSideways = degree;
		_tiltSidewaysPercentage = 0.0;
	}
}
void HuyangNeck::tiltForward(double degree, double duration)
{
	degree = degree + 50;
	degree = constrain(degree, _minTiltForward, _maxTiltForward);

	if (targetTiltForward != degree)
	{
		if (duration == 0)
		{
			double way = 0;
			if (degree > _currentTiltForward)
			{
				way = degree - _currentTiltForward;
			}
			else
			{
				way = _currentTiltForward - degree;
			}

			duration = way * 16;
		}

		_startTiltForward = _currentTiltForward;
		targetTiltForward = degree;
		_tiltForwardDuration = duration;
		_tiltForwardStartMillis = _currentMillis;
	}
}
void HuyangNeck::rotate(double degree, double duration)
{
	degree = constrain(degree, _minRotation, _maxRotation);

	if (targetRotate != degree)
	{
		if (duration == 0)
		{
			double way = 0;
			if (degree > _currentRotate)
			{
				way = degree - _currentRotate;
			}
			else
			{
				way = _currentRotate - degree;
			}

			duration = way * 16;
		}

		_startRotate = _currentRotate;
		targetRotate = degree;
		_rotationDuration = duration;
		_rotationStartMillis = _currentMillis;
	}
}

void HuyangNeck::updateCurrentRotate()
{
	if (_currentRotate != targetRotate)
	{
		double percentage = (_currentMillis - _rotationStartMillis) / _rotationDuration;
		_currentRotate = easeInAndOut(_startRotate, _currentRotate, targetRotate, percentage);

		uint16_t rotateDegree = map(_currentRotate, _minRotation, _maxRotation, 0, 110);
		rotateServo(pwm_pin_head_rotate, rotateDegree);
	}
}

void HuyangNeck::setup()
{
	rotate(0);
	tiltForward(0);
}

void HuyangNeck::doRandomRotate()
{
	if (_randomDoRotate == 0)
	{
		_randomDoRotate = _currentMillis + 2000 + (random(6, 12 + 1) * 1000);
	}

	if (_currentMillis > _randomDoRotate)
	{
		_randomDoRotate = 0;

		if (_currentRotate > 0)
		{
			rotate(-(random(2, 35)), random(2, 6 + 1) * 1000);
		}
		else
		{
			rotate(random(2, 35), random(2, 6 + 1) * 1000);
		}
	}
}

void HuyangNeck::doRandomTiltForward()
{
	if (_randomDoTiltForward == 0)
	{
		_randomDoTiltForward = _currentMillis + 2500 + (random(6, 12 + 1) * 1050);
	}

	if (_currentMillis > _randomDoTiltForward)
	{
		_randomDoTiltForward = 0;

		double workArea = (_maxTiltForward - 50) - (_minTiltForward + 0);
		double center = workArea / 2;

		double randomArea = workArea / 2;

		tiltForward(random(center - randomArea, center + randomArea + 1), random(3, 6 + 1) * 1000);
	}
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