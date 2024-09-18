#ifndef HuyangBody_h
#define HuyangBody_h

#include "Arduino.h"
#include <Adafruit_PWMServoDriver.h>
#include <Adafruit_NeoPixel.h>

// Servo Parameters
#define HuyangBody_SERVOMIN 150	 // This is the 'minimum' pulse length count (out of 4096)
#define HuyangBody_SERVOMAX 595	 // This is the 'maximum' pulse length count (out of 4096)
#define HuyangBody_SERVO_FREQ 60 // Analog servos run at ~50 Hz updates

#define pwm_pin_sideway_left (uint8_t)14
#define pwm_pin_sideway_right (uint8_t)15
#define pwm_pin_forward_left (uint8_t)12
#define pwm_pin_forward_right (uint8_t)13
#define pwm_pin_body_rotate (uint8_t)11

class HuyangBody
{
public:
	HuyangBody(Adafruit_PWMServoDriver *pwm);
	void setup();
	void loop();

	bool automatic = true;

	void tiltBodySideways(int16_t degree);
	void tiltBodyForward(int16_t degree);
	void rotateBody(int16_t degree);

	void centerAll();

	void updateChestLights();

private:
	Adafruit_PWMServoDriver *_pwm;

	unsigned long _currentMillis = 0;
	unsigned long _previousMillis = 0;

	void rotateServo(uint8_t servo, uint16_t degree);

	Adafruit_NeoPixel *_neoPixelLights;
	neoPixelType pixelFormat = NEO_GRB + NEO_KHZ800;
};

#endif