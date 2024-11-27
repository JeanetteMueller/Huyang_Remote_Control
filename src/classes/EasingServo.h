
#ifndef EasingServo_h
#define EasingServo_h

#include "Arduino.h"
#include <Adafruit_PWMServoDriver.h>

class EasingServo
{
public:
    EasingServo(Adafruit_PWMServoDriver *pwm, uint8_t servo, double min, double max, double start);
    void moveServoTo(double degree, double duration = 1000);
    void loop();

    double targetDegree = 0;
    double currentDegree = 0;

private:
    unsigned long _currentMillis = 0;
    unsigned long _previousMillis = 0;

    Adafruit_PWMServoDriver *_pwm;

    uint8_t _servoPin = 0;

    double _min = -100;
    double _max = 100;
    double _start = 0;
    double _duration = 0;
    unsigned long _startMillis = 0;

    void rotateServo(double degree);
    double easeInOutQuad(double t);
    double easeInAndOut(double start, double current, double target, double percentage);
    void updatePosition();
};

#endif