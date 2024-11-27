#include "HuyangNeck.h"

void HuyangNeck::doRandomRotate()
{
	if (_randomDoRotate == 0)
	{
		_randomDoRotate = _currentMillis + 2000 + (random(6, 12 + 1) * 1000);
	}

	if (_currentMillis > _randomDoRotate)
	{
		_randomDoRotate = 0;

		if (_currentRotate > 0)
		{
			rotateHead(-(random(10, 80 + 1)), random(2, 6 + 1) * 1000);
		}
		else
		{
			rotateHead(random(10, 80 + 1), random(2, 6 + 1) * 1000);
		}
	}
}

void HuyangNeck::doRandomTiltForward()
{
	if (_randomDoTiltForward == 0)
	{
		_randomDoTiltForward = _currentMillis + 2500 + (random(6, 12 + 1) * 1050);
	}

	if (_currentMillis > _randomDoTiltForward)
	{
		_randomDoTiltForward = 0;

		double workArea = 60;
		double center = -15;

		tiltNeckForward(random(center - workArea, center + workArea + 1), random(3, 6 + 1) * 1000);
	}
}