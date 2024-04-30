
#ifndef WebServer_h
#define WebServer_h

#include "Arduino.h"
#ifdef ESP32
#include <WiFi.h>
#include <AsyncTCP.h>
#elif defined(ESP8266)
#include <ESPAsyncTCP.h>
#endif

#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

#include "content/styles.h"
#include "content/javascript.h"
#include "content/joystick.h"
#include "content/baseHtml.h"

#include "pages/indexHtml.h"
#include "pages/settingsHtml.h"

class WebServer
{
public:
    enum Page
    {
        indexPage,
        settingsPage
    };

    bool automaticAnimations = true;

    uint16_t leftEye = 3;
    uint16_t rightEye = 3;
    uint16_t allEyes = 0;

    int16_t neckRotate = 0;
    int16_t neckTiltForward = 0;
    int16_t neckTiltSideways = 0;

    int16_t bodyRotate = 0;
    int16_t bodyTiltForward = 0;
    int16_t bodyTiltSideways = 0;

    WebServer(uint32_t port);
    void start();

private:
    AsyncWebServer *_server;
    String html;

    void getBaseHtml(const String &body, String &target);
    String getPage(Page page, AsyncWebServerRequest *request);

    void apiPostAction(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total);

    void notFound(AsyncWebServerRequest *request);
    std::string random_string(size_t length);
};

#endif