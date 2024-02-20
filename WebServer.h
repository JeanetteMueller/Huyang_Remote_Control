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
#include "html.h"

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

void setupWebserver() {
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/html", getIndexPage());
  });

  // Send a GET request to <IP>/get?message=<message>
  server.on("/get", HTTP_GET, [](AsyncWebServerRequest *request) {
    
    if (request->hasParam(ActionStringOpen)) {
      String action = request->getParam(ActionStringOpen)->value();

      if (action == ActionTargetAll){
        leftEyeTargetState = Open;
        rightEyeTargetState = Open;
      } else if(action == ActionTargetLeft) {
        leftEyeTargetState = Open;
      } else if(action == ActionTargetRight) {
        rightEyeTargetState = Open;
      }
      automaticState = AutomaticOff;

    } else if (request->hasParam(ActionStringClose)) {
      String action = request->getParam(ActionStringClose)->value();

      if (action == ActionTargetAll){
        leftEyeTargetState = Closed;
        rightEyeTargetState = Closed;
      }else if(action == ActionTargetLeft) {
        leftEyeTargetState = Closed;
      }else if(action == ActionTargetRight) {
        rightEyeTargetState = Closed;
      }
      automaticState = AutomaticOff;

    } else if (request->hasParam(ActionStringBlink)) {
      String action = request->getParam(ActionStringBlink)->value();

      if (action == ActionTargetAll){
        leftEyeTargetState = Blink;
        rightEyeTargetState = Blink;
      }else if(action == ActionTargetLeft) {
        leftEyeTargetState = Blink;
      }else if(action == ActionTargetRight) {
        rightEyeTargetState = Blink;
      }
      automaticState = AutomaticOff;
    } else if (request->hasParam(ActionStringFocus)) {
      String action = request->getParam(ActionStringFocus)->value();

      if (action == ActionTargetAll){
        leftEyeTargetState = Focus;
        rightEyeTargetState = Focus;
      }else if(action == ActionTargetLeft) {
        leftEyeTargetState = Focus;
      }else if(action == ActionTargetRight) {
        rightEyeTargetState = Focus;
      }
      automaticState = AutomaticOff;
    } else if (request->hasParam(ActionStringSad)) {
      String action = request->getParam(ActionStringSad)->value();

      if (action == ActionTargetAll){
        leftEyeTargetState = Sad;
        rightEyeTargetState = Sad;
      }else if(action == ActionTargetLeft) {
        leftEyeTargetState = Sad;
      }else if(action == ActionTargetRight) {
        rightEyeTargetState = Sad;
      }
      automaticState = AutomaticOff;
    } else if (request->hasParam(ActionStringAngry)) {
      String action = request->getParam(ActionStringAngry)->value();

      if (action == ActionTargetAll){
        leftEyeTargetState = Angry;
        rightEyeTargetState = Angry;
      }else if(action == ActionTargetLeft) {
        leftEyeTargetState = Angry;
      }else if(action == ActionTargetRight) {
        rightEyeTargetState = Angry;
      }
      automaticState = AutomaticOff;
    }
    
    if (request->hasParam(ActionStringAutomatic)) {
      String action = request->getParam(ActionStringAutomatic)->value();

      if (action == ActionStringAutomaticOn){
        automaticState = AutomaticOn;
      }else if (action == ActionStringAutomaticOff){
        automaticState = AutomaticOff;
      }
    }

    randomDuration = 0;

    request->send(200, "text/html", getIndexPage());
  });

  server.onNotFound(notFound);

  server.begin();
}

void loopWebserver() {
}