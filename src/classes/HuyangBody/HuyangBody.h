#ifndef HuyangBody_h
#define HuyangBody_h

#include "Arduino.h"
#include <Adafruit_PWMServoDriver.h>
#include <Adafruit_NeoPixel.h>

class HuyangBody
{
public:
	HuyangBody(Adafruit_PWMServoDriver *pwm);
	void setup();
	void loop();

	bool automatic = true;

	void tiltBodySideways(uint16_t degree);
	void tiltBodyForward(uint16_t degree);
	void rotateBody(uint16_t degree);

	void centerAll();

	void updateChestLights();

private:
	Adafruit_PWMServoDriver *_pwm;

	unsigned long _currentMillis = 0;
	unsigned long _previousMillis = 0;

	int16_t _centerTiltSideways = 50;
	int16_t _centerTiltFront_left = 20;
	int16_t _centerTiltFront_right = 100;

	void rotateServo(uint8_t servo, uint16_t degree);

	Adafruit_NeoPixel *_neoPixelLights;
	neoPixelType pixelFormat = NEO_GRB + NEO_KHZ800;
};

#endif