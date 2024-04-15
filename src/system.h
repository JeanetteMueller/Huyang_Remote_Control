
void setup()
{
  Serial.begin(115200); // Used only for debugging on arduino serial monitor
  Serial.println(F("Huyang! v1.6"));

  wifi->currentMode = WiFiDefaultMode;

  // Wifi Settings
  wifi->host = IPAddress(192, 168, 10, 1);
  wifi->subnetMask = IPAddress(255, 255, 255, 0);
  wifi->currentMode = JxWifiManager::WifiModeNetwork;

  // Hotspot
  wifi->hotspot_Ssid = WifiSsidOfHotspot;
  wifi->hotspot_Password = WifiPasswordHotspot;

  // use Local Wifi
  wifi->network_Ssid = WifiSsidConnectTo; // <- change if needed
  wifi->network_Password = WifiPasswordConnectTo;

  wifi->setup();

  pwm->begin();
  pwm->setOscillatorFrequency(27000000);
  pwm->setPWMFreq(60);


  setupWebserver();

  huyangFace->setup();
  huyangBody->setup();
  huyangNeck->setup();

  Serial.println(F("setup done"));
}

void loop()
{
  wifi->loop();

  huyangFace->loop();
  huyangBody->loop();
  huyangNeck->loop();
}
