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
    void tiltSideways(uint16_t degree);
    void tiltForward(uint16_t degree);
    void rotate(int16_t degree);

private:
    Adafruit_PWMServoDriver *_pwm;

    unsigned long _currentMillis = 0;
    unsigned long _previousMillis = 0;

    // int16_t _centerTiltSideways = 50;
    // int16_t _centerTiltFront_left = 20;
    // int16_t _centerTiltFront_right = 100;
    // int16_t _centerRotation = 35;

    void rotateServo(uint8_t servo, uint16_t degree);
};

#endif