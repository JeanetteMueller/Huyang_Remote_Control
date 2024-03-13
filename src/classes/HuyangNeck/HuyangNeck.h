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
    void rotate(double degree);

    uint8_t step = 0;
    int16_t currentTiltSideways = 0;
    uint16_t currentTiltForward = 0;
    

    int16_t targetTiltSideways = 0;
    uint16_t targetTiltForward = 0;

    double targetRotate = 0;

private:
    Adafruit_PWMServoDriver *_pwm;

    unsigned long _currentMillis = 0;
    unsigned long _previousMillis = 0;

    int16_t _minTiltSideways = -25;
    int16_t _maxTiltSideways = 25;

    uint16_t _minTiltForward = 0;
    uint16_t _maxTiltForward = 100;

    double _currentRotate = 0;
    double _minRotation = -45;
    double _maxRotation = 45;
    double _startRotate = 0;
    double _rotationPercentage = 1.0;

    void rotateServo(uint8_t servo, uint16_t degree);
    void updateNeckPosition();
    void updateCurrentRotate();
    // int16_t easeInAndOutSpeed = 1;
    // int16_t easeInAndOutMinSpeed = 1;
    // int16_t easeInAndOutMaxSpeed = 5;
    double easeInAndOut(double start, double current, double target, double percentage);
    int16_t getMaxSpeedRange(int16_t speed, int16_t step);
};

#endif