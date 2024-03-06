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

private:
    Adafruit_PWMServoDriver *_pwm;

    unsigned long _currentMillis = 0;
    unsigned long _previousMillis = 0;

    int16_t _targetTiltSideways = 0;
    uint16_t _targetTiltForward = 0;
    int16_t _targetRotate = 0;

    void rotateServo(uint8_t servo, uint16_t degree);
    void updateNeckPosition();
};

#endif