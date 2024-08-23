
#ifndef WebServer_h
#define WebServer_h

#include "Arduino.h"

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
	void setup(bool enableEyes,
			   bool enableMonacle,
			   bool enableNeckMovement,
			   bool enableHeadRotation,
			   bool enableBodyMovement,
			   bool enableBodyRotation,
			   bool enableTorsoLights);
	void start();

private:
	AsyncWebServer *_server;
	String _html;

	bool _enableEyes;
	bool _enableMonacle;
	bool _enableNeckMovement;
	bool _enableHeadRotation;
	bool _enableBodyMovement;
	bool _enableBodyRotation;
	bool _enableTorsoLights;

	void getBaseHtml(const String &body, String &target);
	String getPage(Page page, AsyncWebServerRequest *request);

	void apiPostAction(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total);

	void notFound(AsyncWebServerRequest *request);
};

#endif