#include "HuyangBody.h"
#include <Adafruit_PWMServoDriver.h>

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
	int16_t calibrationShift = -22;  // max 0 to -60
	int16_t calibratedDegree = map(degree, -100, 100, -60 + calibrationShift, 60 + calibrationShift);
	uint16_t rotateDegree = map(calibratedDegree, -100, 100, 0, 170);

	rotateServo(pwm_pin_sideway_left, rotateDegree + 0);
	rotateServo(pwm_pin_sideway_right, rotateDegree + 15);
}
void HuyangBody::tiltBodyForward(int16_t degree)
{
	int16_t calibrationShift = 40; // max 0 to 40
	uint16_t rotateDegree = map(degree, -100, 100, 30 + calibrationShift, 140 + calibrationShift);

	rotateServo(pwm_pin_forward_left, rotateDegree);
	rotateServo(pwm_pin_forward_right, 180 - rotateDegree);
}
void HuyangBody::rotateBody(int16_t degree)
{
	int16_t calibrationShift = 0; // max 0 to 20
	uint16_t rotateDegree = map(degree, -100, 100, 0 + calibrationShift, 70 + calibrationShift);
	rotateServo(pwm_pin_body_rotate, rotateDegree);
}

void HuyangBody::centerAll()
{
	tiltBodySideways(0);
	delay(500);

	tiltBodyForward(0);
	delay(500);

	rotateBody(0);
	delay(500);
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
    centerAll();

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