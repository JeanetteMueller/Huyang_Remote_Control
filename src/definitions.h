


JxWifiManager *wifi = new JxWifiManager();

Arduino_DataBus *leftBus = new Arduino_HWSPI(0 /* DC */, 15 /* CS */);
Arduino_GFX *leftEye = new Arduino_GC9A01(leftBus, 0 /* RST */);

Arduino_DataBus *rightBus = new Arduino_HWSPI(0 /* DC */, 16 /* CS */);
Arduino_GFX *rightEye = new Arduino_GC9A01(rightBus, 0 /* RST */);

Adafruit_PWMServoDriver *pwm = new Adafruit_PWMServoDriver(0x40);

HuyangFace *huyangFace = new HuyangFace(leftEye, rightEye);
HuyangBody *huyangBody = new HuyangBody(pwm); 
HuyangNeck *huyangNeck = new HuyangNeck(pwm);

HuyangAudio *huyangAudio = new HuyangAudio();

WebServer *webserver = new WebServer(WebServerPort);