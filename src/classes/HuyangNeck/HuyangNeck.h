#ifndef HuyangNeck_h
#define HuyangNeck_h

#include "Arduino.h"
#include <Adafruit_PWMServoDriver.h>

class HuyangNeck
{
public:
    HuyangNeck(Adafruit_PWMServoDriver *pwm);
    void setup();
    void loop();
    void tiltSideways(int16_t degree);
    void tiltForward(uint16_t degree);
    void rotate(int16_t degree);

    uint8_t step = 0;
    int16_t currentTiltSideways = 0;
    uint16_t currentTiltForward = 0;
    int16_t currentRotate = 0;

    int16_t targetTiltSideways = 0;
    uint16_t targetTiltForward = 0;
    int16_t targetRotate = 0;

private:
    Adafruit_PWMServoDriver *_pwm;

    unsigned long _currentMillis = 0;
    unsigned long _previousMillis = 0;

    int16_t _minTiltSideways = -20;
	int16_t _maxTiltSideways = 20;

    uint16_t _minTiltForward = 0;
	uint16_t _maxTiltForward = 100;

    int16_t _minRotation = -45;
	int16_t _maxRotation = 45;

    void rotateServo(uint8_t servo, uint16_t degree);
    void updateNeckPosition();
    void updateCurrentRotate();
    int16_t easeInAndOutSpeed = 1;
    int16_t easeInAndOutSpeedRamp = 5;
    int16_t easeInAndOutMinSpeed = 1;
    int16_t easeInAndOutMaxSpeed = 21;
    int16_t easeInAndOut(int16_t current, int16_t target);
    int16_t getMaxSpeedRange(int16_t speed, int16_t step);
};

#endif