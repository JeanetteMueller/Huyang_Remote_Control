#include "EasingServo.h"
#include <Adafruit_PWMServoDriver.h>

EasingServo::EasingServo(Adafruit_PWMServoDriver *pwm, uint8_t servo, double min, double max, double start)
{
    _pwm = pwm;
    _servoPin = servo;
    _start = start;
    _min = min;
    _max = max;
}

void EasingServo::rotateServo(double degree)
{
    // Serial.println("HuyangNeck rotateServo create pulselength");

    uint16_t pulselength = map(degree, 0, 180, _min, _max); //  Calibrate the positive range (see below)

    // Serial.print("rotateServoToDegree Servo: ");
    // Serial.print(servo);
    // Serial.print(" to Degree: ");
    // Serial.print(degree);
    // Serial.print(" with Pulselength: ");
    // Serial.println(pulselength);

    // Serial.println("HuyangNeck rotateServo set PWM");

    _pwm->setPWM(_servoPin, 0, pulselength);
    // Serial.println("done");
}

double EasingServo::easeInOutQuad(double t)
{
    return t < 0.5 ? 2 * t * t : t * (4 - 2 * t) - 1;
}

double EasingServo::easeInAndOut(double start, double current, double target, double percentage)
{
    double result = target;

    if (percentage > 1.0)
    {
        percentage = 1.0;
    }

    if (current != target)
    {
        // Serial.print("easeInAndOut from ");
        // Serial.print(start);
        // Serial.print(" to ");
        // Serial.print(target);
        // Serial.print(":  current ");
        // Serial.print(current);

        double easeInOut = easeInOutQuad(percentage);

        if (current < target)
        {
            double subTarget = (target - start);

            result = start + (subTarget * easeInOut);

            if (result > target)
            {
                result = target;
            }
        }
        else if (current > target)
        {
            double subTarget = (start - target);

            result = start - (subTarget * easeInOut);

            if (result < target)
            {
                result = target;
            }
        }

        // Serial.print(":   ");
        // Serial.print(result);
    }

    return result;
}

void EasingServo::moveServoTo(double degree, double duration)
{
    degree = constrain(degree, _min, _max);

	if (targetDegree != degree)
	{
		if (duration == 0)
		{
			double way = 0;
			if (degree > currentDegree)
			{
				way = degree - currentDegree;
			}
			else
			{
				way = currentDegree - degree;
			}

			duration = way * 16;
		}

		_start = currentDegree;
		targetDegree = degree;
		_duration = duration;
		_startMillis = _currentMillis;
	}
}

void EasingServo::updatePosition()
{
	if (currentDegree != targetDegree)
	{
		double percentage = (_currentMillis - _startMillis) / _duration;
		currentDegree = easeInAndOut(_start, currentDegree, targetDegree, percentage);
	}

	rotateServo(currentDegree);
}
void EasingServo::loop()
{
    _currentMillis = millis();
	if (_currentMillis - _previousMillis >= 20)
	{
		_previousMillis = _currentMillis;

		updatePosition();
	}
}