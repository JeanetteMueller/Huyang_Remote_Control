#ifndef HuyangFace_h
#define HuyangFace_h

#include "Arduino.h"
#include <Arduino_GFX_Library.h>

#define tftColor(r, g, b) ((((r) & 0xF8) << 8) | (((g) & 0xFC) << 3) | ((b) >> 3))

class HuyangFace
{
public:
	enum EyeState
	{
		Open,
		Closed,
		Blink,
		Focus,
		Sad,
		Angry
	};

	HuyangFace(Arduino_GFX *left, Arduino_GFX *right);

	void setup();
	void loop();

	bool automatic = true;

	void setEyesTo(EyeState newState);
	void setLeftEyeTo(EyeState newState);
	void setRightEyeTo(EyeState newState);

private:
	Arduino_GFX *_leftEye;
	Arduino_GFX *_rightEye;
	unsigned long _currentMillis = 0;
	unsigned long _previousMillis = 0;
	
	uint16_t _tftDisplayWidth = 240;
	uint16_t _tftDisplayHeight = 240;

	uint16_t _huyangEyeColor = tftColor(255 - 255, 255 - 221, 255 - 34); // 0xFD20
	uint16_t _huyangClosedEyeColor = tftColor(255, 255, 255);

	EyeState _leftEyeTargetState = Blink;
	EyeState _rightEyeTargetState = Blink;

	EyeState _leftEyeState = Closed;
	EyeState _rightEyeState = Closed;
	
	uint32_t _randomDuration = 2000;
	uint16_t _blinkDelay = 1;

	void openEyesLoop();
	void openEyes(uint16_t color);
	void openEye(Arduino_GFX *eye, uint16_t color);

	void closeEyesLoop();
	void closeEyes(uint16_t color);
	void closeEye(Arduino_GFX *eye, uint16_t color);

	void focusEyesLoop();
	void focusEyes(uint16_t color);
	void focusEye(Arduino_GFX *eye, uint16_t color);

	void sadEyesLoop();
	void sadEyes(uint16_t color);
	void sadEye(Arduino_GFX *eye, bool inner, uint16_t color);

	void angryEyesLoop();
	void angryEyes(uint16_t color);
};

#endif