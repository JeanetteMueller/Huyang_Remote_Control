#ifndef HuyangAudio_h
#define HuyangAudio_h

#include "Arduino.h"
#include <SoftwareSerial.h>
#include <DFPlayerMini_Fast.h>

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

    DFPlayerMini_Fast player;
    EspSoftwareSerial::UART audioSerial;

    uint16_t audioPause = 2000;
    uint16_t audioItemCount = 0;
};

#endif