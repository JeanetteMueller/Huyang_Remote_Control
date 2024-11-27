#include "HuyangAudio.h"

#define AudioSerialPort_TX -1
#define AudioSerialPort_RX 12

void printDetail(uint8_t type, int value);

HuyangAudio::HuyangAudio()
{
	_audioSerial.begin(9600, SWSERIAL_8N1, AudioSerialPort_RX, AudioSerialPort_TX);
}

void HuyangAudio::setup()
{

	bool debugOutputFromPlayer = true;

	Serial.println("HuyangAudio setup");

	if (!_audioSerial)
	{ // If the object did not initialize, then its configuration is invalid
		Serial.println("SoftwareSerial is not working right, check config");
		while (1)
		{ // Don't continue with invalid configuration
			delay(1000);
		}
	}
	else
	{
		_isSerialReady = true;
	}

	if (_isSerialReady)
	{

		if (!_player.begin(_audioSerial, /*isACK = */ false, /*doReset = */ false))
		{
			Serial.println("Connecting to DFPlayer Mini failed!");
		}
		else
		{
			_isPlayerReady = true;
		}

		if (_isPlayerReady)
		{

			Serial.println("Player IS READY");

			_player.volume(25);
		}
	}
}
void HuyangAudio::loop()
{
	if (_isSerialReady && _isPlayerReady)
	{

		_currentMillis = millis();

		if (_currentMillis < _previousMillis)
		{
			_previousMillis = 0;
		}

		if (_currentMillis - _previousMillis >= _audioPause)
		{
			// _player.printError();

			if (_player.available())
			{
				Serial.println(_player.readType(), _player.read()); // Print the detail message from DFPlayer to handle different errors and states.

				Serial.println("player is NOT playing");

				_previousMillis = _currentMillis;

				if (_audioItemCount == 0)
				{
					int count = _player.readFileCounts();

					if (count > 0)
					{
						_audioItemCount = count;

						Serial.print("Found Number of mp3 Files: ");
						Serial.println(count);
					}
					else
					{
						_audioItemCount = 1;
					}
				}

				if (_audioItemCount > 0)
				{
					uint16_t randomItemNumber = random(1, _audioItemCount + 1);

					if (randomItemNumber == 8)
					{
						randomItemNumber = randomItemNumber + 1;
					}

					Serial.print("Play item Number ");
					Serial.print(randomItemNumber);
					Serial.print(" of ");
					Serial.print(_audioItemCount);
					Serial.println(" Items ");

					_player.play(randomItemNumber);

					_audioPause = 2000 + (random(10, 50) * 100);
				}
				else
				{
					// Serial.println("no mp3s to play");
				}
			}
		}
	}
}
/*
void HuyangAudio::setup()
{



	audioSerial.begin(38400, SWSERIAL_8N1, AudioSerialPort_RX, AudioSerialPort_TX, false);

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
		_isSerialReady = true;
	}

	if (_isSerialReady)
	{
		if (!player.begin(mySerial, false)) {  //Use softwareSerial to communicate with mp3.
			Serial.println(F("Unable to begin:"));
			Serial.println(F("1.Please recheck the connection!"));

		}

		_previousMillis = millis() + 5000;
		if (player.begin(audioSerial, false))
		{
			_isPlayerReady = true;

			player.volume(30);
		}
		else
		{
			Serial.println(F("Please remove and insert the SD card again!"));
		}

		if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
			Serial.println(F("Please remove and insert the SD card again!"));
		}
		Serial.println("DFPlayer Mini online.");
	}
	else
	{
		Serial.println("Software Serial Setup failed.");
	}
}

void HuyangAudio::loop()
{
	Serial.println("HuyangAudio loop");

	if (_isSerialReady && _isPlayerReady)
	{

		_currentMillis = millis();

		if (_currentMillis < _previousMillis)
		{
			_previousMillis = 0;
		}


			// if (audioVolumeValue != 1500)
			// {
			// 	uint16_t newVolume = map(audioVolumeValue, 1000, 2000, 30, 15);
			// 	player.volume(newVolume);
			// }
			// else
			// {
			// 	//----Set volume----
			// 	player.volume(30); // Set volume value (0~30).
			// }

			// if (player.isPlaying())
			// {
			// 	Serial.println(F("player is playing"));
			// 	previousMillisAudio = currentMillis;
			// }


		if (_currentMillis - _previousMillis >= audioPause)
		{
			//player.printError();

			if (!player.isPlaying())
			{
				// Serial.println("player is NOT playing");

				_previousMillis = _currentMillis;

				if (audioItemCount == 0)
				{
					int count = player.numSdTracks();

					if (count > 0)
					{
						audioItemCount = count;

						Serial.print("Found Number of mp3 Files: ");
						Serial.println(count);
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
					//Serial.println("no mp3s to play");
				}
			}
		}
	}
}

*/

void printDetail(uint8_t type, int value)
{
	switch (type)
	{
	case TimeOut:
		Serial.println(F("Time Out!"));
		break;
	case WrongStack:
		Serial.println(F("Stack Wrong!"));
		break;
	case DFPlayerCardInserted:
		Serial.println(F("Card Inserted!"));
		break;
	case DFPlayerCardRemoved:
		Serial.println(F("Card Removed!"));
		break;
	case DFPlayerCardOnline:
		Serial.println(F("Card Online!"));
		break;
	case DFPlayerUSBInserted:
		Serial.println("USB Inserted!");
		break;
	case DFPlayerUSBRemoved:
		Serial.println("USB Removed!");
		break;
	case DFPlayerPlayFinished:
		Serial.print(F("Number:"));
		Serial.print(value);
		Serial.println(F(" Play Finished!"));
		break;
	case DFPlayerError:
		Serial.print(F("DFPlayerError:"));
		switch (value)
		{
		case Busy:
			Serial.println(F("Card not found"));
			break;
		case Sleeping:
			Serial.println(F("Sleeping"));
			break;
		case SerialWrongStack:
			Serial.println(F("Get Wrong Stack"));
			break;
		case CheckSumNotMatch:
			Serial.println(F("Check Sum Not Match"));
			break;
		case FileIndexOut:
			Serial.println(F("File Index Out of Bound"));
			break;
		case FileMismatch:
			Serial.println(F("Cannot Find File"));
			break;
		case Advertise:
			Serial.println(F("In Advertise"));
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}
