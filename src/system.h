void setup() {
  Serial.begin(115200);  //Used only for debugging on arduino serial monitor
  Serial.println(F("Huyang! v1.4"));

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
