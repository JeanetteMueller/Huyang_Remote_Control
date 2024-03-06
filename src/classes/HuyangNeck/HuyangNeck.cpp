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

void HuyangNeck::updateNeckPosition()
{
	uint16_t leftDegree = map(_targetTiltForward + _targetTiltSideways, 0, 100, 65, 10);
	uint16_t rightDegree = map(_targetTiltForward - _targetTiltSideways, 0, 100, 35, 90);

	uint16_t leftDegreeMin = 10;
	uint16_t leftDegreeMax = 65;

	uint16_t rightDegreeMin = 35;
	uint16_t rightDegreeMax = 90;

	leftDegree = min(leftDegree, leftDegreeMax);
	leftDegree = max(leftDegree, leftDegreeMin);
	
	rightDegree = min(rightDegree, rightDegreeMax);
	rightDegree = max(rightDegree, rightDegreeMin);

	rotateServo(pwm_pin_head_left, leftDegree);
	rotateServo(pwm_pin_head_right, rightDegree);
}
void HuyangNeck::tiltSideways(int16_t degree)
{
	int16_t minRotation = -20;
	int16_t maxRotation = 20;

	degree = min(degree, maxRotation);
	degree = max(degree, minRotation);

	_targetTiltSideways = degree;
	currentTiltSideways = degree;
	updateNeckPosition();
}
void HuyangNeck::tiltForward(uint16_t degree)
{
	uint16_t minRotation = 0;
	uint16_t maxRotation = 100;

	degree = min(degree, maxRotation);
	degree = max(degree, minRotation);

	_targetTiltForward = degree;
	currentTiltForward = degree;
	updateNeckPosition();
}
void HuyangNeck::rotate(int16_t degree)
{
	int16_t minRotation = -45;
	int16_t maxRotation = 45;

	degree = min(degree, maxRotation);
	degree = max(degree, minRotation);

	_targetRotate = degree;

	currentRotate = degree;
	uint16_t rotateDegree = map(degree, minRotation, maxRotation, 5, 85);
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