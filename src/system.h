#include "wifi/Wifi.h"
#include "webserver/WebServer.h"


void setup() {
  Serial.begin(115200);  //Used only for debugging on arduino serial monitor
  Serial.println(F("Huyang! v1.5"));

  pwm->begin();
  pwm->setOscillatorFrequency(27000000);
  pwm->setPWMFreq(60);

  setupWifi();

  setupWebserver();

  huyangFace->setup();
  huyangBody->setup();
  huyangNeck->setup();

  Serial.println(F("setup done"));
}

void loop() {
  loopWifi();

  huyangFace->loop();
  huyangBody->loop();
  huyangNeck->loop();
}
