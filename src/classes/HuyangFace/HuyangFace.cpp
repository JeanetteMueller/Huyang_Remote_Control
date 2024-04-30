
#include "HuyangFace.h"
#include <Arduino_GFX_Library.h>

HuyangFace::EyeState HuyangFace::getStateFrom(const char *stateString)
{
	if (stateString == "open")
	{
		return HuyangFace::EyeState::Open;
	}
	else if (stateString == "close")
	{
		return HuyangFace::EyeState::Closed;
	}
	else if (stateString == "blink")
	{
		return HuyangFace::EyeState::Blink;
	}
	else if (stateString == "focus")
	{
		return HuyangFace::EyeState::Focus;
	}
	else if (stateString == "sad")
	{
		return HuyangFace::EyeState::Sad;
	}
	else if (stateString == "angry")
	{
		return HuyangFace::EyeState::Angry;
	}

	return HuyangFace::EyeState::Open;
}

void HuyangFace::setEyesTo(EyeState newState)
{
	if (_leftEyeLastSelectedState != newState || _rightEyeLastSelectedState != newState)
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
	if (_leftEyeLastSelectedState != newState)
	{
		_leftEyeLastSelectedState = newState;
		_leftEyeTargetState = newState;
		automatic = false;
		_randomDuration = 0;
	}
}
void HuyangFace::setRightEyeTo(EyeState newState)
{
	if (_rightEyeLastSelectedState != newState)
	{
		_rightEyeLastSelectedState = newState;
		_rightEyeTargetState = newState;
		automatic = false;
		_randomDuration = 0;
	}
}

void HuyangFace::openEyesLoop()
{
	if ((_leftEyeTargetState == Open || _leftEyeTargetState == Blink) || (_rightEyeTargetState == Open || _rightEyeTargetState == Blink))
	{
		bool shouldDoLeftEye = (_leftEyeTargetState == Open || _leftEyeTargetState == Blink);
		bool shouldDoRightEye = (_rightEyeTargetState == Open || _rightEyeTargetState == Blink);

		if (shouldDoLeftEye && _leftEyeState != Open && shouldDoRightEye && _rightEyeState != Open)
		{
			openEyes(_huyangEyeColor);
			_leftEyeState = Open;
			_rightEyeState = Open;
		}
		else if ((_leftEyeTargetState == Open || _leftEyeTargetState == Blink) && _leftEyeState != Open)
		{
			openEye(_leftEye, _huyangEyeColor);
			_leftEyeState = Open;
		}
		else if ((_rightEyeTargetState == Open || _rightEyeTargetState == Blink) && _rightEyeState != Open)
		{
			openEye(_rightEye, _huyangEyeColor);
			_rightEyeState = Open;
		}

		if (_leftEyeTargetState == Blink)
		{
			_leftEyeTargetState = Open;
		}
		if (_rightEyeTargetState == Blink)
		{
			_rightEyeTargetState = Open;
		}
	}
}

void HuyangFace::openEyes(uint16_t color)
{
	Serial.println("openEyes");

	for (uint16_t step = 0; step <= _tftDisplayHeight / 2; step++)
	{
		uint16_t position = (_tftDisplayHeight / 2) - step;

		_leftEye->drawFastHLine(0, position, _tftDisplayWidth, color);
		_rightEye->drawFastHLine(0, position, _tftDisplayWidth, color);
		_leftEye->drawFastHLine(0, _tftDisplayHeight - position, _tftDisplayWidth, color);
		_rightEye->drawFastHLine(0, _tftDisplayHeight - position, _tftDisplayWidth, color);

		while (_currentMillis - _previousMillis < _blinkDelay)
		{
			_currentMillis = millis();
		}
		_previousMillis = _currentMillis;
	}
}

void HuyangFace::openEye(Arduino_GFX *eye, uint16_t color)
{
	Serial.println("openEye");

	for (uint16_t step = 0; step <= _tftDisplayHeight / 2; step++)
	{
		uint16_t position = (_tftDisplayHeight / 2) - step;

		eye->drawFastHLine(0, position, _tftDisplayWidth, color);
		eye->drawFastHLine(0, _tftDisplayHeight - position, _tftDisplayWidth, color);

		while (_currentMillis - _previousMillis < _blinkDelay)
		{
			_currentMillis = millis();
		}
		_previousMillis = _currentMillis;
	}
}

void HuyangFace::closeEyesLoop()
{
	if (_currentMillis - _previousMillis > _randomDuration)
	{

		if ((_leftEyeTargetState == Closed || _leftEyeTargetState == Blink) || (_rightEyeTargetState == Closed || _rightEyeTargetState == Blink))
		{

			if ((_leftEyeTargetState == Closed || _leftEyeTargetState == Blink) && _leftEyeState != Closed && (_rightEyeTargetState == Closed || _rightEyeTargetState == Blink) && _rightEyeState != Closed)
			{
				closeEyes(_huyangClosedEyeColor);
				_leftEyeState = Closed;
				_rightEyeState = Closed;
			}
			else if ((_leftEyeTargetState == Closed || _leftEyeTargetState == Blink) && _leftEyeState != Closed)
			{
				closeEye(_leftEye, _huyangClosedEyeColor);
				_leftEyeState = Closed;
			}
			else if ((_rightEyeTargetState == Closed || _rightEyeTargetState == Blink) && _rightEyeState != Closed)
			{
				closeEye(_rightEye, _huyangClosedEyeColor);
				_rightEyeState = Closed;
			}
		}
	}
}

void HuyangFace::closeEyes(uint16_t color)
{
	Serial.println("closeEyes");

	for (uint16_t step = 0; step <= _tftDisplayHeight / 2; step++)
	{

		_leftEye->drawFastHLine(0, step, _tftDisplayWidth, color);
		_rightEye->drawFastHLine(0, step, _tftDisplayWidth, color);
		_leftEye->drawFastHLine(0, _tftDisplayHeight - step, _tftDisplayWidth, color);
		_rightEye->drawFastHLine(0, _tftDisplayHeight - step, _tftDisplayWidth, color);

		while (_currentMillis - _previousMillis < _blinkDelay)
		{
			_currentMillis = millis();
		}
		_previousMillis = _currentMillis;
	}
}

void HuyangFace::closeEye(Arduino_GFX *eye, uint16_t color)
{
	Serial.println("closeEye");
	for (uint16_t step = 0; step <= _tftDisplayHeight / 2; step++)
	{
		eye->drawFastHLine(0, step, _tftDisplayWidth, color);
		eye->drawFastHLine(0, _tftDisplayHeight - step, _tftDisplayWidth, color);

		while (_currentMillis - _previousMillis < _blinkDelay)
		{
			_currentMillis = millis();
		}
		_previousMillis = _currentMillis;
	}
}

void HuyangFace::focusEyesLoop()
{
	if (_leftEyeTargetState == Focus || _rightEyeTargetState == Focus)
	{

		bool shoudlDoLeftEye = _leftEyeTargetState == Focus && _leftEyeState != Focus;
		bool shoudlDoRightEye = _rightEyeTargetState == Focus && _rightEyeState != Focus;

		if (shoudlDoLeftEye && shoudlDoRightEye)
		{
			focusEyes(_huyangClosedEyeColor);
			_leftEyeState = Focus;
			_rightEyeState = Focus;
		}
		else if (_leftEyeTargetState == Focus && _leftEyeState != Focus)
		{
			focusEye(_leftEye, _huyangClosedEyeColor);
			_leftEyeState = Focus;
		}
		else if (_rightEyeTargetState == Focus && _rightEyeState != Focus)
		{
			focusEye(_rightEye, _huyangClosedEyeColor);
			_rightEyeState = Focus;
		}
	}
}

void HuyangFace::focusEyes(uint16_t color)
{
	Serial.println("focusEyes");

	for (uint16_t step = 0; step <= ((_tftDisplayHeight / 2) / 6 * 4); step++)
	{

		_leftEye->drawFastHLine(0, step, _tftDisplayWidth, color);
		_rightEye->drawFastHLine(0, step, _tftDisplayWidth, color);
		_leftEye->drawFastHLine(0, _tftDisplayHeight - step, _tftDisplayWidth, color);
		_rightEye->drawFastHLine(0, _tftDisplayHeight - step, _tftDisplayWidth, color);

		while (_currentMillis - _previousMillis < _blinkDelay)
		{
			_currentMillis = millis();
		}
		_previousMillis = _currentMillis;
	}
}
void HuyangFace::focusEye(Arduino_GFX *eye, uint16_t color)
{
	Serial.println("focusEye");

	for (uint16_t step = 0; step <= ((_tftDisplayHeight / 2) / 6 * 4); step++)
	{
		eye->drawFastHLine(0, step, _tftDisplayWidth, color);
		eye->drawFastHLine(0, _tftDisplayHeight - step, _tftDisplayWidth, color);

		while (_currentMillis - _previousMillis < _blinkDelay)
		{
			_currentMillis = millis();
		}
		_previousMillis = _currentMillis;
	}
}

void HuyangFace::sadEyesLoop()
{
	if (_leftEyeTargetState == Sad || _rightEyeTargetState == Sad)
	{

		bool shoudlDoLeftEye = (_leftEyeTargetState == Sad && _leftEyeState != Sad);
		bool shoudlDoRightEye = (_rightEyeTargetState == Sad && _rightEyeState != Sad);

		if (shoudlDoLeftEye && shoudlDoRightEye)
		{
			sadEyes(_huyangClosedEyeColor);
			_leftEyeState = Sad;
			_rightEyeState = Sad;
		}
		else if (_leftEyeTargetState == Sad && _leftEyeState != Sad)
		{
			sadEye(_leftEye, true, _huyangClosedEyeColor);
			_leftEyeState = Sad;
		}
		else if (_rightEyeTargetState == Sad && _rightEyeState != Sad)
		{
			sadEye(_rightEye, false, _huyangClosedEyeColor);
			_rightEyeState = Sad;
		}
	}
}

void HuyangFace::sadEyes(uint16_t color)
{
	Serial.println("sadEyes");

	uint16_t length = _tftDisplayHeight;

	for (uint16_t step = 0; step <= _tftDisplayHeight; step++)
	{
		_leftEye->drawFastHLine(_tftDisplayHeight - length, _tftDisplayHeight - step, length, color);
		_rightEye->drawFastHLine(0, _tftDisplayHeight - step, length, color);
		length = length - 2;

		while (_currentMillis - _previousMillis < _blinkDelay)
		{
			_currentMillis = millis();
		}
		_previousMillis = _currentMillis;
	}
}
void HuyangFace::sadEye(Arduino_GFX *eye, bool inner, uint16_t color)
{
	Serial.println("sadEye");
	uint16_t length = _tftDisplayHeight;
	uint16_t left = 0;

	for (uint16_t step = 0; step <= _tftDisplayHeight; step++)
	{

		if (inner == true)
		{
			left = _tftDisplayHeight - length;
		}

		eye->drawFastHLine(left, _tftDisplayHeight - step, length, color);

		length = length - 2;

		while (_currentMillis - _previousMillis < _blinkDelay)
		{
			_currentMillis = millis();
		}
		_previousMillis = _currentMillis;
	}
}

void HuyangFace::angryEyesLoop()
{
	if (_leftEyeTargetState == Angry || _rightEyeTargetState == Angry)
	{

		bool shoudlDoLeftEye = (_leftEyeTargetState == Angry && _leftEyeState != Angry);
		bool shoudlDoRightEye = (_rightEyeTargetState == Angry && _rightEyeState != Angry);

		if (shoudlDoLeftEye && shoudlDoRightEye)
		{
			angryEyes(_huyangClosedEyeColor);
			_leftEyeState = Angry;
			_rightEyeState = Angry;
		}
		else if (_leftEyeTargetState == Angry && _leftEyeState != Angry)
		{
			sadEye(_leftEye, false, _huyangClosedEyeColor);
			_leftEyeState = Angry;
		}
		else if (_rightEyeTargetState == Angry && _rightEyeState != Angry)
		{
			sadEye(_rightEye, true, _huyangClosedEyeColor);
			_rightEyeState = Angry;
		}
	}
}

void HuyangFace::angryEyes(uint16_t color)
{
	Serial.println("angryEyes");

	uint16_t length = _tftDisplayHeight;

	for (uint16_t step = 0; step <= _tftDisplayHeight; step++)
	{

		_leftEye->drawFastHLine(0, _tftDisplayHeight - step, length, color);
		_rightEye->drawFastHLine(_tftDisplayHeight - length, _tftDisplayHeight - step, length, color);
		length = length - 2;

		while (_currentMillis - _previousMillis < _blinkDelay)
		{
			_currentMillis = millis();
		}
		_previousMillis = _currentMillis;
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

	if (automatic == true)
	{
		_randomDuration = random(6, 12 + 1) * 1000;
		_leftEyeTargetState = Blink;
		_rightEyeTargetState = Blink;
	}
}