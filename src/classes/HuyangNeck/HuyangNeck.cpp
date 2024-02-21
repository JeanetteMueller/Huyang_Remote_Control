#include "HuyangNeck.h"

HuyangNeck::HuyangNeck(Adafruit_PWMServoDriver pwm) {
	_pwm = pwm;
}

void HuyangNeck::setup()
{
	
}

void HuyangNeck::loop()
{
	_currentMillis = millis();

}