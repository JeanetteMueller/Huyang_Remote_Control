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
    void tiltSideways(double degree);
    void tiltForward(double degree, double duration = 0);
    void rotate(double degree, double duration = 0);

    bool automatic = true;

    double targetTiltSideways = 0;
    double targetTiltForward = 0;
    double targetRotate = 0;

private:
    Adafruit_PWMServoDriver *_pwm;

    unsigned long _currentMillis = 0;
    unsigned long _previousMillis = 0;

    unsigned long _randomDoRotate = 0;
    unsigned long _randomDoTiltForward = 0;

    double _currentTiltSideways = 0;
    double _minTiltSideways = -25;
    double _maxTiltSideways = 25;
    double _startTiltSideways = 0;
    double _tiltSidewaysPercentage = 1.0;

    double _currentTiltForward = 50;
    double _minTiltForward = 00;
    double _maxTiltForward = 90;
    double _startTiltForward = 50;
    double _tiltForwardDuration = 0;
    unsigned long _tiltForwardStartMillis = 0;

    double _currentRotate = 0;
    double _minRotation = -45;
    double _maxRotation = 45;
    double _startRotate = 0;
    double _rotationDuration = 0;
    unsigned long _rotationStartMillis = 0;

    void rotateServo(uint8_t servo, double degree);
    void updateNeckPosition();
    void updateCurrentRotate();
    double easeInAndOut(double start, double current, double target, double percentage);
    int16_t getMaxSpeedRange(int16_t speed, int16_t step);

    void doRandomRotate();
	void doRandomTiltForward();
};

#endif