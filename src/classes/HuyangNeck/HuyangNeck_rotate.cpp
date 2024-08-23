#include "HuyangNeck.h"

void HuyangNeck::rotateHead(double degree, double duration)
{
	degree = constrain(degree, _minRotation, _maxRotation);

	if (targetRotate != degree)
	{
		if (duration == 0)
		{
			double way = 0;
			if (degree > _currentRotate)
			{
				way = degree - _currentRotate;
			}
			else
			{
				way = _currentRotate - degree;
			}

			duration = way * 16;
		}

		_startRotate = _currentRotate;
		targetRotate = degree;
		_rotationDuration = duration;
		_rotationStartMillis = _currentMillis;
	}
}

void HuyangNeck::updateCurrentRotate()
{
	if (_currentRotate != targetRotate)
	{
		double percentage = (_currentMillis - _rotationStartMillis) / _rotationDuration;
		_currentRotate = easeInAndOut(_startRotate, _currentRotate, targetRotate, percentage);

		uint16_t rotateDegree = map(_currentRotate, _minRotation, _maxRotation, 0, 110);
		rotateServo(pwm_pin_head_rotate, rotateDegree);
	}
}