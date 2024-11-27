
#include "HuyangFace.h"
#include <Arduino_GFX_Library.h>

HuyangFace::EyeState HuyangFace::getStateFrom(uint8_t state)
{
	if (state == 1)
	{
		return HuyangFace::EyeState::Open;
	}
	else if (state == 2)
	{
		return HuyangFace::EyeState::Closed;
	}
	else if (state == 3)
	{
		return HuyangFace::EyeState::Blink;
	}
	else if (state == 4)
	{
		return HuyangFace::EyeState::Focus;
	}
	else if (state == 5)
	{
		return HuyangFace::EyeState::Sad;
	}
	else if (state == 6)
	{
		return HuyangFace::EyeState::Angry;
	}

	return HuyangFace::EyeState::None;
}

void HuyangFace::setEyesTo(EyeState newState)
{
	if (_leftEyeTargetState != newState || _rightEyeTargetState != newState)
	{
		_leftEyeLastSelectedState = newState;
		_rightEyeLastSelectedState = newState;
		_leftEyeTargetState = newState;
		_rightEyeTargetState = newState;
		automatic = false;
		_randomDuration = 0;
	}
}
void HuyangFace::setLeftEyeTo(EyeState newState)
{
	if (_leftEyeTargetState != newState)
	{
		_leftEyeLastSelectedState = newState;
		_leftEyeTargetState = newState;
		automatic = false;
		_randomDuration = 0;
	}
}
void HuyangFace::setRightEyeTo(EyeState newState)
{
	if (_rightEyeTargetState != newState)
	{
		_rightEyeLastSelectedState = newState;
		_rightEyeTargetState = newState;
		automatic = false;
		_randomDuration = 0;
	}
}

HuyangFace::HuyangFace(Arduino_GFX *left, Arduino_GFX *right)
{
	_leftEye = left;
	_rightEye = right;
}

void HuyangFace::setup()
{
	_currentMillis = millis();
	_previousMillis = _currentMillis;

	_leftEye->begin();
	_rightEye->begin();

	_leftEye->fillScreen(_huyangEyeColor);
	_rightEye->fillScreen(_huyangEyeColor);

	delay(500);
}

void HuyangFace::loop()
{
	_currentMillis = millis();

	if (_previousMillis > _currentMillis)
	{
		_previousMillis = _currentMillis;
	}

	closeEyesLoop();

	if (_currentMillis - _previousMillis > 100)
	{
		openEyesLoop();
		focusEyesLoop();
		sadEyesLoop();
		angryEyesLoop();
	}

	if (automatic == true && _currentMillis > _previousRandomMillis + _randomDuration)
	{
		_previousRandomMillis = _currentMillis;
		
		_randomDuration = random(3, 6 + 1) * 1000;

		if (_leftEyeTargetState == Closed || _rightEyeTargetState == Closed) {
			_leftEyeTargetState = Open;
			_rightEyeTargetState = Open;
			return;
		}

		if (_leftEyeTargetState != Open || _rightEyeTargetState != Open) {
			_leftEyeTargetState = Closed;
			_rightEyeTargetState = Closed;

			_randomDuration = 250;
			return;
		}

		uint8_t moodType = random(0, 5 + 1);

		switch (moodType)
		{
		case 3:
			_leftEyeTargetState = Focus;
			_rightEyeTargetState = Focus;
			break;
		case 4:
			_leftEyeTargetState = Sad;
			_rightEyeTargetState = Sad;
			break;
		case 5:
			_leftEyeTargetState = Angry;
			_rightEyeTargetState = Angry;
			break;
		default:
			_randomDuration = random(6, 10 + 1) * 1000;
			_leftEyeTargetState = Blink;
			_rightEyeTargetState = Blink;
			break;
		}
	}
}