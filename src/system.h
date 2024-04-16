
void setup()
{
    Serial.begin(115200); // Used only for debugging on arduino serial monitor
    Serial.println("Huyang! v1.6");

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

    webserver->start();

    pwm->begin();
    pwm->setOscillatorFrequency(27000000);
    pwm->setPWMFreq(60);

    huyangFace->setup();
    huyangBody->setup();
    huyangNeck->setup();

    Serial.println("setup done");
}

void loop()
{
    wifi->loop();

    huyangFace->automatic = webserver->automaticAnimations;

    if (NULL != webserver->allEyes)
    {
        Serial.println("update both eyes");
        HuyangFace::EyeState newState = huyangFace->getStateFrom(webserver->allEyes);
        huyangFace->setEyesTo(newState);
        webserver->allEyes = NULL;
        webserver->automaticAnimations = huyangFace->automatic;
    }
    else
    {
        if (NULL != webserver->leftEye)
        {
            Serial.println("update left eye");
            HuyangFace::EyeState newState = huyangFace->getStateFrom(webserver->leftEye);
            huyangFace->setLeftEyeTo(newState);
            webserver->leftEye = NULL;
            webserver->automaticAnimations = huyangFace->automatic;
        }

        if (NULL != webserver->rightEye)
        {
            Serial.println("update right eye");
            HuyangFace::EyeState newState = huyangFace->getStateFrom(webserver->rightEye);
            huyangFace->setRightEyeTo(newState);
            webserver->rightEye = NULL;
            webserver->automaticAnimations = huyangFace->automatic;
        }
    }

    

    huyangFace->loop();

    huyangNeck->rotate(webserver->neckRotate);
    huyangNeck->tiltForward(webserver->neckTiltForward);
    huyangNeck->tiltSideways(webserver->neckTiltSideways);
    huyangNeck->loop();

    huyangBody->rotate(webserver->bodyRotate);
    huyangBody->tiltForward(webserver->bodyTiltForward);
    huyangBody->tiltSideways(webserver->bodyTiltSideways);
    huyangBody->loop();
}
