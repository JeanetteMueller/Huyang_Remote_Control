#include "HuyangNeck.h"

void HuyangNeck::tiltNeckSideways(double degree)
{
	degree = constrain(degree, _minTiltSideways, _maxTiltSideways);

	degree = map(degree, _minTiltSideways, _maxTiltSideways, -50, 50);

	if (targetTiltSideways != degree)
	{
		_startTiltSideways = _currentTiltSideways;
		targetTiltSideways = degree;
		_tiltSidewaysPercentage = 0.0;
	}
}
void HuyangNeck::tiltNeckForward(double degree, double duration)
{
	degree = degree + 100;
	degree = constrain(degree, _minTiltForward, _maxTiltForward);

	if (targetTiltForward != degree)
	{
		if (duration == 0)
		{
			double way = 0;
			if (degree > _currentTiltForward)
			{
				way = degree - _currentTiltForward;
			}
			else
			{
				way = _currentTiltForward - degree;
			}

			duration = way * 16;
		}

		_startTiltForward = _currentTiltForward;
		targetTiltForward = degree;
		_tiltForwardDuration = duration;
		_tiltForwardStartMillis = _currentMillis;
	}
}