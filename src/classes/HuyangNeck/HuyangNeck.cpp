#include "HuyangNeck.h"
#include <Adafruit_PWMServoDriver.h>

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

int16_t HuyangNeck::easeInAndOut(int16_t current, int16_t target)
{
	int16_t result = target;

	if (current != target)
	{
		int16_t maxSpeedRange = getMaxSpeedRange(easeInAndOutSpeed, easeInAndOutSpeedRamp);

		Serial.print(F("easeInAndOut from "));
		Serial.print(current);
		Serial.print(F(" to "));
		Serial.print(target);
		Serial.print(F("     with speed "));
		Serial.print(easeInAndOutSpeed);
		Serial.print(F("     maxSpeedRange "));
		Serial.print(maxSpeedRange);
		Serial.print(F(":        "));

		if (current < target)
		{
			result = current + easeInAndOutSpeed;
			if (result > target)
			{
				result = target;
			}

			if (target - (current + easeInAndOutSpeed) < maxSpeedRange)
			{
				Serial.print(F(" Speed DOWN "));
				easeInAndOutSpeed = easeInAndOutSpeed - easeInAndOutSpeedRamp;
			}
			else if (target - (current + result) > maxSpeedRange)
			{
				Serial.print(F(" Speed UP "));
				easeInAndOutSpeed = easeInAndOutSpeed + easeInAndOutSpeedRamp;
			}
			else
			{
				Serial.print(F(" Speed NO CHANGE "));
			}

			if (easeInAndOutSpeed < easeInAndOutMinSpeed) {
				easeInAndOutSpeed = easeInAndOutMinSpeed;
			}else if (easeInAndOutSpeed > easeInAndOutMaxSpeed) {
				easeInAndOutSpeed = easeInAndOutMaxSpeed;
			}
			// Serial.println(F(""));
			// Serial.print(F(" new easeInAndOutSpeed "));
			// Serial.println(easeInAndOutSpeed);
		}
		else if (current > target)
		{
			result = current - easeInAndOutSpeed;
			if (result < target)
			{
				result = target;
			}
		}

		Serial.print(F(":        "));
		Serial.println(result);
	}else{
		easeInAndOutSpeed = easeInAndOutMinSpeed;
	}

	return result;
}

int16_t HuyangNeck::getMaxSpeedRange(int16_t speed, int16_t step)
{
	int16_t result = 0;

	for (int16_t i = 0; i < speed; i = i + step)
	{
		result = result + speed;
		result = result - i;
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

	easeInAndOutSpeed = easeInAndOutMinSpeed;
}
void HuyangNeck::tiltForward(uint16_t degree)
{
	degree = min(degree, _maxTiltForward);
	degree = max(degree, _minTiltForward);

	targetTiltForward = degree;
	currentTiltForward = degree;

	easeInAndOutSpeed = easeInAndOutMinSpeed;
}
void HuyangNeck::rotate(int16_t degree)
{
	degree = min(degree, _maxRotation);
	degree = max(degree, _minRotation);

	targetRotate = degree;

	easeInAndOutSpeed = easeInAndOutMinSpeed;
}

void HuyangNeck::updateCurrentRotate()
{
	currentRotate = easeInAndOut(currentRotate, targetRotate);

	uint16_t rotateDegree = map(currentRotate, _minRotation, _maxRotation, 5, 85);
	rotateServo(pwm_pin_head_rotate, rotateDegree);
}

void HuyangNeck::setup()
{
	rotate(0);
	tiltForward(0);
}

void HuyangNeck::loop()
{
	_currentMillis = millis();
	if (_currentMillis - _previousMillis > 50)
	{
		_previousMillis = _currentMillis;

		updateNeckPosition();

		updateCurrentRotate();
	}

	// if (_currentMillis - _previousMillis >= 2000)
	// {
	// 	step++;
	// 	_previousMillis = _currentMillis;
	// }

	// if (step == 1)
	// {
	// 	//centered
	// 	rotate(0);

	// 	// //unten
	// 	tiltForward(0);
	// 	// // rotateServo(pwm_pin_head_left, 	70);
	// 	// // rotateServo(pwm_pin_head_right, 30);
	// }
	// else if (step == 2)
	// {
	// 	// //oben
	// 	tiltForward(100);
	// 	// // rotateServo(pwm_pin_head_left, 	10);
	// 	// // rotateServo(pwm_pin_head_right, 90);
	// }
	// else if (step == 3)
	// {
	// 	// //unten
	// 	tiltForward(0);
	// 	// // rotateServo(pwm_pin_head_left, 	70);
	// 	// // rotateServo(pwm_pin_head_right, 30);
	// }
	// else if (step == 4)
	// {
	// 	// rechts
	// 	rotate(20);
	// }
	// else if (step == 5)
	// {
	// 	// links
	// 	rotate(-20);

	// 	step = 0;
	// }
}