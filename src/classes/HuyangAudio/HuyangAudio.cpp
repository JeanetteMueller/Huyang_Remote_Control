#include "HuyangAudio.h"

#define MYPORT_TX 0
#define MYPORT_RX 12

HuyangAudio::HuyangAudio()
{
	// audioSerial = SoftwareSerial(29, 28); // RX, TX
}

void HuyangAudio::setup()
{

	Serial.println("Initializing DFPlayer ... ");

	audioSerial.begin(38400, SWSERIAL_8N1, MYPORT_RX, MYPORT_TX, false);

	if (!audioSerial)
	{ // If the object did not initialize, then its configuration is invalid
		Serial.println("Invalid EspSoftwareSerial pin configuration, check config");
		while (1)
		{ // Don't continue with invalid configuration
			delay(1000);
		}
	}
	else
	{
		_isReady = true;
	}

	if (_isReady)
	{

		// if (!player.begin(mySerial, false)) {  //Use softwareSerial to communicate with mp3.
		//     Serial.println(F("Unable to begin:"));
		//     Serial.println(F("1.Please recheck the connection!"));

		// }

		_previousMillis = millis() + 5000;
		player.begin(audioSerial, false);
		player.volume(30);

		// if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
		//	Serial.println(F("Please remove and insert the SD card again!"));
		// }
		Serial.println("DFPlayer Mini online.");
	}
	else
	{
		Serial.println("Software Serial Setup failed.");
	}
}

void HuyangAudio::loop()
{
	// Serial.println("HuyangAudio loop");

	_currentMillis = millis();

	if (_currentMillis < _previousMillis)
	{
		_previousMillis = 0;
	}

	/*
		if (audioVolumeValue != 1500)
		{
			uint16_t newVolume = map(audioVolumeValue, 1000, 2000, 30, 15);
			player.volume(newVolume);
		}
		else
		{
			//----Set volume----
			player.volume(30); // Set volume value (0~30).
		}

		if (player.isPlaying())
		{
			Serial.println(F("player is playing"));
			previousMillisAudio = currentMillis;
		}
	*/

	if (_currentMillis - _previousMillis >= audioPause)
	{
		Serial.println("currentMillis right");
		// player.printError();

		if (!player.isPlaying())
		{
			Serial.println("player is NOT playing");

			_previousMillis = _currentMillis;

			if (audioItemCount == 0)
			{
				int count = player.numSdTracks();
				Serial.println(count);
				if (count > 0)
				{
					audioItemCount = count;
				}
			}

			if (audioItemCount > 0)
			{
				uint16_t randomItemNumber = random(1, audioItemCount + 1);

				if (randomItemNumber == 8)
				{
					randomItemNumber = randomItemNumber + 1;
				}

				Serial.print("Play item Number ");
				Serial.print(randomItemNumber);
				Serial.print(" of ");
				Serial.print(audioItemCount);
				Serial.println(" Items ");

				player.play(randomItemNumber);

				audioPause = 2000 + (random(10, 50) * 100);
			}
			else
			{
				Serial.println("no mp3s to play");
			}
		}
	}
}