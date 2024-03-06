#include <Arduino.h>
#ifdef ESP32
#include <WiFi.h>
#include <AsyncTCP.h>
#elif defined(ESP8266)
#include <ESPAsyncTCP.h>
#endif

#include <ESPAsyncWebServer.h>

AsyncWebServer server(ServerPort);

#define ActionStringOpen String("open")
#define ActionStringClose String("close")
#define ActionStringFocus String("focus")
#define ActionStringSad String("sad")
#define ActionStringAngry String("angry")
#define ActionStringBlink String("blink")
#define ActionStringAutomatic String("automatic")
#define ActionStringAutomaticOn String("on")
#define ActionStringAutomaticOff String("off")
#define ActionTargetAll String("all")
#define ActionTargetLeft String("left")
#define ActionTargetRight String("right")

#include "styles.h"
#include "baseHtml.h"
#include "javascript.h"
#include "form.h"

// html always last
#include "html.h"

void notFound(AsyncWebServerRequest *request)
{
  request->send(404, "text/plain", "Not found");
}

void postAction(AsyncWebServerRequest *request)
{
  Serial.println("ACTION!");

  int params = request->params();
  for (int i = 0; i < params; i++)
  {
    AsyncWebParameter *p = request->getParam(i);
    Serial.printf("POST[%s]: %s\n", p->name().c_str(), p->value().c_str());

    if (p->name() == "neckRotate")
    {
      huyangNeck->rotate(atoi(p->value().c_str()));
    }

    if (p->name() == "neckTiltForward")
    {
      huyangNeck->tiltForward(atoi(p->value().c_str()));
    }

    if (p->name() == "neckTiltSideways")
    {
      huyangNeck->tiltSideways(atoi(p->value().c_str()));
    }
  }
  request->send(200, "text/html", getIndexPage());
}

void setupWebserver()
{
  server.on("/get", HTTP_POST, postAction);
  server.on("/", HTTP_POST, postAction);

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(200, "text/html", getIndexPage()); });

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(200, "text/html", getIndexPage()); });

  // Send a GET request to <IP>/get?message=<message>
  server.on("/get", HTTP_GET, [](AsyncWebServerRequest *request)
            {
    
    if (request->hasParam(ActionStringOpen)) {
      String action = request->getParam(ActionStringOpen)->value();

      if (action == ActionTargetAll){
        huyangFace->setEyesTo(HuyangFace::EyeState::Open);
      } else if(action == ActionTargetLeft) {
        huyangFace->setLeftEyeTo(HuyangFace::EyeState::Open);
      } else if(action == ActionTargetRight) {
        huyangFace->setRightEyeTo(HuyangFace::EyeState::Open);
      }

    } else if (request->hasParam(ActionStringClose)) {
      String action = request->getParam(ActionStringClose)->value();

      if (action == ActionTargetAll){
        huyangFace->setEyesTo(HuyangFace::EyeState::Closed);
      }else if(action == ActionTargetLeft) {
        huyangFace->setLeftEyeTo(HuyangFace::EyeState::Closed);
      }else if(action == ActionTargetRight) {
        huyangFace->setRightEyeTo(HuyangFace::EyeState::Closed);
      }

    } else if (request->hasParam(ActionStringBlink)) {
      String action = request->getParam(ActionStringBlink)->value();

      if (action == ActionTargetAll){
        huyangFace->setEyesTo(HuyangFace::EyeState::Blink);
      }else if(action == ActionTargetLeft) {
        huyangFace->setLeftEyeTo(HuyangFace::EyeState::Blink);
      }else if(action == ActionTargetRight) {
        huyangFace->setRightEyeTo(HuyangFace::EyeState::Blink);
      }
    } else if (request->hasParam(ActionStringFocus)) {
      String action = request->getParam(ActionStringFocus)->value();

      if (action == ActionTargetAll){
        huyangFace->setEyesTo(HuyangFace::EyeState::Focus);
      }else if(action == ActionTargetLeft) {
        huyangFace->setLeftEyeTo(HuyangFace::EyeState::Focus);
      }else if(action == ActionTargetRight) {
        huyangFace->setRightEyeTo(HuyangFace::EyeState::Focus);
      }
    } else if (request->hasParam(ActionStringSad)) {
      String action = request->getParam(ActionStringSad)->value();

      if (action == ActionTargetAll){
        huyangFace->setEyesTo(HuyangFace::EyeState::Sad);
      }else if(action == ActionTargetLeft) {
        huyangFace->setLeftEyeTo(HuyangFace::EyeState::Sad);
      }else if(action == ActionTargetRight) {
        huyangFace->setRightEyeTo(HuyangFace::EyeState::Sad);
      }
    } else if (request->hasParam(ActionStringAngry)) {
      String action = request->getParam(ActionStringAngry)->value();

      if (action == ActionTargetAll){
        huyangFace->setEyesTo(HuyangFace::EyeState::Angry);
      }else if(action == ActionTargetLeft) {
        huyangFace->setLeftEyeTo(HuyangFace::EyeState::Angry);
      }else if(action == ActionTargetRight) {
        huyangFace->setRightEyeTo(HuyangFace::EyeState::Angry);
      }
    }
    
    if (request->hasParam(ActionStringAutomatic)) {
      String action = request->getParam(ActionStringAutomatic)->value();

      if (action == ActionStringAutomaticOn){
        huyangFace->automatic = true;
      }else if (action == ActionStringAutomaticOff){
        huyangFace->automatic = false;
      }
    }

    request->send(200, "text/html", getIndexPage()); });

  server.onNotFound(notFound);

  server.begin();
}