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

void HuyangNeck::tiltSideways(uint16_t degree)
{
}
void HuyangNeck::tiltForward(uint16_t degree)
{
	currentTiltForward = degree;
	uint16_t leftDegree = map(degree, 0, 100, 68, 10);
	uint16_t rightDegree = map(degree, 0, 100, 32, 90);

	rotateServo(pwm_pin_head_left, leftDegree);
	rotateServo(pwm_pin_head_right, rightDegree);
}
void HuyangNeck::rotate(int16_t degree)
{
	if (degree > 45)
	{
		degree = 45;
	}
	else if (degree < -45)
	{
		degree = -45;
	}
	currentRotate = degree;
	uint16_t rotateDegree = map(degree, -45, 45, 0, 90);
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