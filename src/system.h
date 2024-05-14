
void setup()
{
    Serial.begin(115200); // Used only for debugging on arduino serial monitor
    Serial.println("Huyang! v1.7 by Jeanette Müller");

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

    if (huyangFace->automatic == false)
    {
        if (webserver->allEyes != 0)
        {
            Serial.println("update both eyes");
            HuyangFace::EyeState newState = huyangFace->getStateFrom(webserver->allEyes);
            huyangFace->setEyesTo(newState);

            if (newState == HuyangFace::EyeState::Blink)
            {
                webserver->allEyes = HuyangFace::EyeState::Open;
            }
        }
        else
        {
            if (webserver->leftEye != 0)
            {
                HuyangFace::EyeState newState = huyangFace->getStateFrom(webserver->leftEye);
                huyangFace->setLeftEyeTo(newState);

                if (newState == HuyangFace::EyeState::Blink)
                {
                    webserver->leftEye = HuyangFace::EyeState::Open;
                }
            }

            if (webserver->rightEye != 0)
            {
                HuyangFace::EyeState newState = huyangFace->getStateFrom(webserver->rightEye);
                huyangFace->setRightEyeTo(newState);

                if (newState == HuyangFace::EyeState::Blink)
                {
                    webserver->rightEye = HuyangFace::EyeState::Open;
                }
            }
        }
    }

    huyangFace->loop();

    huyangNeck->automatic = webserver->automaticAnimations;
    if (huyangNeck->automatic == false)
    {
        huyangNeck->rotate(webserver->neckRotate);
        huyangNeck->tiltForward(webserver->neckTiltForward);
        huyangNeck->tiltSideways(webserver->neckTiltSideways);
    }
    huyangNeck->loop();

    huyangBody->automatic = webserver->automaticAnimations;
    if (huyangBody->automatic == false)
    {
        huyangBody->rotate(webserver->bodyRotate);
        huyangBody->tiltForward(webserver->bodyTiltForward);
        huyangBody->tiltSideways(webserver->bodyTiltSideways);
    }
    huyangBody->loop();
}
