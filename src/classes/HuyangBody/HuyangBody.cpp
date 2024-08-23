#include "HuyangBody.h"
#include <Adafruit_PWMServoDriver.h>

// Servo Parameters
#define HuyangBody_SERVOMIN 150	 // This is the 'minimum' pulse length count (out of 4096)
#define HuyangBody_SERVOMAX 595	 // This is the 'maximum' pulse length count (out of 4096)
#define HuyangBody_SERVO_FREQ 60 // Analog servos run at ~50 Hz updates

#define pwm_pin_sideway_left (uint8_t)14
#define pwm_pin_sideway_right (uint8_t)15
#define pwm_pin_forward_left (uint8_t)12
#define pwm_pin_forward_right (uint8_t)13
#define pwm_pin_body_rotate (uint8_t)11

HuyangBody::HuyangBody(Adafruit_PWMServoDriver *pwm)
{
	_pwm = pwm;

	_neoPixelLights = new Adafruit_NeoPixel(2, 0, pixelFormat);
	_neoPixelLights->setBrightness(20);
	_neoPixelLights->begin();
}

void HuyangBody::rotateServo(uint8_t servo, uint16_t degree)
{
	uint16_t pulselength = map(degree, 0, 180, HuyangBody_SERVOMIN, HuyangBody_SERVOMAX); //  Calibrate the positive range (see below)
	
	// Serial.print("HuyangBody rotateServo: ");
	// Serial.print(servo);
	// Serial.print(" to Degree: ");
	// Serial.print(degree);
	// Serial.print(" with Pulselength: ");
	// Serial.println(pulselength);
	
	_pwm->setPWM(servo, 0, pulselength);
	// Serial.println("done");
}

void HuyangBody::tiltBodySideways(int16_t degree)
{

	uint16_t rotateDegree = map(degree, -100, 100, 0, 180);

	rotateServo(pwm_pin_sideway_left, rotateDegree);
	rotateServo(pwm_pin_sideway_right, rotateDegree);
}
void HuyangBody::tiltBodyForward(int16_t degree)
{
	uint16_t rotateDegree = map(degree, -100, 100, 0, 180);

	rotateServo(pwm_pin_forward_left, rotateDegree);
	rotateServo(pwm_pin_forward_right, 180 - rotateDegree);
}
void HuyangBody::rotateBody(int16_t degree)
{
	// center = 35
	uint16_t rotateDegree = map(degree, -100, 100, 0, 70);
	rotateServo(pwm_pin_body_rotate, rotateDegree);
}

void HuyangBody::centerAll()
{
	tiltBodySideways(0);
	tiltBodyForward(0);
	rotateBody(0);
}

void HuyangBody::updateChestLights()
{
	uint32_t colorDefaultBlue = _neoPixelLights->Color(0, 0, 128);

	_neoPixelLights->setPixelColor(0, colorDefaultBlue);
	_neoPixelLights->setPixelColor(1, colorDefaultBlue);

	_neoPixelLights->show();
}

void HuyangBody::setup()
{
}

void HuyangBody::loop()
{
	_currentMillis = millis();

	if (_previousMillis > _currentMillis)
	{
		_previousMillis = _currentMillis;
	}

	if (_currentMillis - _previousMillis > 100)
	{
		updateChestLights();
	}
}