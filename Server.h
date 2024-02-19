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

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

String prepareEyeHtml(String name) {
  String s = "";

  s += "<div style=\"";
  s += "display: block;";
  s += "position:relative;";
  s += "float:left;";
  s += "margin:auto;";
  s += "width:48%;";
  s += "height:300px;";
  s += "text-align:center;";
  s += "background-color: #333;";
  s += "border-radius: 10px;";
  s += "\">";

  s += "<a href=\"/get?" + ActionStringBlink + "=" + name + "\">";

  s += "<div style=\"";
  s += "display: block;";
  s += "margin:auto;";
  s += "width:100px;height: 100px;";
  s += "text-align:center;";
  s += "border-radius: 50px;";
  s += "background-color: #fd2;";
  s += "\">";

  s += "<h5 style=\"padding: 34px 0 0 0;\">BLINK</h5>";
  
  s += "</div>";
  s += "</a>";

  s += "<a href=\"/get?" + ActionStringClose + "=" + name + "\" class=\"button\">CLOSE</a> ";
  s += "<a href=\"/get?" + ActionStringOpen + "=" + name + "\" class=\"button\">OPEN</a> ";
  s += "<br />";
  s += "<a href=\"/get?" + ActionStringFocus + "=" + name + "\" class=\"button\">FOCUS</a> ";
  s += "<a href=\"/get?" + ActionStringSad + "=" + name + "\" class=\"button\">SAD</a> ";
  s += "<a href=\"/get?" + ActionStringAngry + "=" + name + "\" class=\"button\">ANGRY</a>";
  s += "</div>";

  return s;
}

String getPage() {
  String s = "";
  s += "<!DOCTYPE HTML>\r\n<html>\r\n";
  s += "<head>\r\n";
  s += "<title>Huyang Control</title>\r\n";
  s += "<meta name=\"viewport\" content=\"width=device-width, minimal-ui\">";
  s += "<meta name=\"apple-mobile-web-app-capable\" content=\"yes\" />";
  s += "<style>";

  s += "body {";
  s += "font-family: 'Helvetica', 'Arial', sans-serif;";
  s += "font-size: 16pt;";
  s += "background-color: #000;";
  s += "color: #fff;";
  s += "}";

  s += "";

  s += "#container {";
  s += "display: flex;";
  s += "flex-wrap: wrap;";
  s += "justify-content: center;";
  s += "}";

  s += "a:link, a:visited, a:active {";
  s += "color: #fff;";
  s += "text-decoration: none;";
  s += "}";

  s += ".button {";
  s += "background-color: #333;";
  s += "display: inline-block;";
  s += "padding: 5px;";
  s += "margin: 5px;";
  s += "color: #fff;";
  s += "text-decoration: none;";
  s += "border-radius: 5px;";
  s += "}";


  s += "h5 {";
  s += "font-family: 'Helvetica', 'Arial', sans-serif;";
  s += "font-size: 22pt;";
  s += "display: flex;";
  s += "align-items: center;";
  s += "justify-content: center;";
  s += "width:100%;";
  s += "text-align:center;";
  s += "color: #000;";
  s += "}";

  s += "</style>";
  s += "</head>\r\n";

  s += "<body>\r\n";
  s += "<div id=\"container\">";
  s += "<div style=\"";
  s += "display: block;";

  s += "width:100%;";
  s += "height:50px;";
  s += "text-align:center;";
  s += "\">";

  if (automaticState == AutomaticOn) {
    s += "<a href=\"/get?" + ActionStringAutomatic + "=" + ActionStringAutomaticOff + "\" class=\"button\">Auto is ON</a>";
  }else{
    s += "<a href=\"/get?" + ActionStringAutomatic + "=" + ActionStringAutomaticOn + "\" class=\"button\">Auto is OFF</a>";
  }

  s += " - ";
  s += "<a href=\"/get?" + ActionStringOpen + "=" + ActionTargetAll + "\" class=\"button\">OPEN</a>";
  s += " - ";
  s += "<a href=\"/get?" + ActionStringClose + "=" + ActionTargetAll + "\" class=\"button\">CLOSE</a>";
  s += " - ";
  s += "<a href=\"/get?" + ActionStringBlink + "=" + ActionTargetAll + "\" class=\"button\">BLINK</a>";
  s += " - ";
  s += "<a href=\"/get?" + ActionStringFocus + "=" + ActionTargetAll + "\" class=\"button\">FOCUS</a>";
  s += " - ";
  s += "<a href=\"/get?" + ActionStringSad + "=" + ActionTargetAll + "\" class=\"button\">SAD</a>";
  s += " - ";
  s += "<a href=\"/get?" + ActionStringAngry + "=" + ActionTargetAll + "\" class=\"button\">ANGRY</a>";
  s += "</div>";

  s += prepareEyeHtml(ActionTargetLeft);
  s += prepareEyeHtml(ActionTargetRight);

  s += "</div>";
  s += "</body>\n";
  s += "</html>\n";

  return s;
}

void setupWebserver() {
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/html", getPage());
  });

  // Send a GET request to <IP>/get?message=<message>
  server.on("/get", HTTP_GET, [](AsyncWebServerRequest *request) {
    
    if (request->hasParam(ActionStringOpen)) {
      String action = request->getParam(ActionStringOpen)->value();

      if (action == ActionTargetAll){
        leftEyeOpen = false;
        leftEyeState = Open;
        rightEyeOpen = false;
        rightEyeState = Open;
      } else if(action == ActionTargetLeft) {
        leftEyeOpen = false;
        leftEyeState = Open;
      } else if(action == ActionTargetRight) {
        rightEyeOpen = false;
        rightEyeState = Open;
      }
      automaticState = AutomaticOff;

    } else if (request->hasParam(ActionStringClose)) {
      String action = request->getParam(ActionStringClose)->value();

      if (action == ActionTargetAll){
        leftEyeOpen = true;
        leftEyeState = Closed;
        rightEyeOpen = true;
        rightEyeState = Closed;
      }else if(action == ActionTargetLeft) {
        leftEyeOpen = true;
        leftEyeState = Closed;
      }else if(action == ActionTargetRight) {
        rightEyeOpen = true;
        rightEyeState = Closed;
      }
      automaticState = AutomaticOff;

    } else if (request->hasParam(ActionStringBlink)) {
      String action = request->getParam(ActionStringBlink)->value();

      if (action == ActionTargetAll){
        leftEyeState = Blink;
        rightEyeState = Blink;
      }else if(action == ActionTargetLeft) {
        leftEyeState = Blink;
      }else if(action == ActionTargetRight) {
        rightEyeState = Blink;
      }
      automaticState = AutomaticOff;
    } else if (request->hasParam(ActionStringFocus)) {
      String action = request->getParam(ActionStringFocus)->value();

      if (action == ActionTargetAll){
        leftEyeState = Focus;
        rightEyeState = Focus;
      }else if(action == ActionTargetLeft) {
        leftEyeState = Focus;
      }else if(action == ActionTargetRight) {
        rightEyeState = Focus;
      }
      automaticState = AutomaticOff;
    } else if (request->hasParam(ActionStringSad)) {
      String action = request->getParam(ActionStringSad)->value();

      if (action == ActionTargetAll){
        leftEyeState = Sad;
        rightEyeState = Sad;
      }else if(action == ActionTargetLeft) {
        leftEyeState = Sad;
      }else if(action == ActionTargetRight) {
        rightEyeState = Sad;
      }
      automaticState = AutomaticOff;
    } else if (request->hasParam(ActionStringAngry)) {
      String action = request->getParam(ActionStringAngry)->value();

      if (action == ActionTargetAll){
        leftEyeState = Angry;
        rightEyeState = Angry;
      }else if(action == ActionTargetLeft) {
        leftEyeState = Angry;
      }else if(action == ActionTargetRight) {
        rightEyeState = Angry;
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

    request->send(200, "text/html", getPage());
  });

  server.onNotFound(notFound);

  server.begin();
}

void loopWebserver() {
}