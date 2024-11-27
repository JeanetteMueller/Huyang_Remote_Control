#ifndef HuyangAudio_h
#define HuyangAudio_h

#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

class HuyangAudio
{
public:
	HuyangAudio();
	void setup();
	void loop();

private:
	unsigned long _currentMillis = 0;
	unsigned long _previousMillis = 0;

	bool _isSerialReady = false;
	bool _isPlayerReady = false;

	DFRobotDFPlayerMini _player;
	SoftwareSerial _audioSerial;

	uint16_t _audioPause = 2000;
	uint16_t _audioItemCount = 0;
};

#endif