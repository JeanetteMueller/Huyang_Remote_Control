
void closeEyes(uint16_t color) {
  Serial.println(F("closeEyes"));

  for (uint16_t step = 0; step <= tftDisplayHeight / 2; step++) {

    leftEye->drawFastHLine(0, step, tftDisplayWidth, color);
    rightEye->drawFastHLine(0, step, tftDisplayWidth, color);
    leftEye->drawFastHLine(0, tftDisplayHeight - step, tftDisplayWidth, color);
    rightEye->drawFastHLine(0, tftDisplayHeight - step, tftDisplayWidth, color);

    while (currentMillis - previousMillis < blinkDelay) {
      currentMillis = millis();
    }
    previousMillis = currentMillis;
  }
}

void openEyes(uint16_t color) {
  Serial.println(F("openEyes"));

  for (uint16_t step = 0; step <= tftDisplayHeight / 2; step++) {
    uint16_t position = (tftDisplayHeight / 2) - step;

    leftEye->drawFastHLine(0, position, tftDisplayWidth, color);
    rightEye->drawFastHLine(0, position, tftDisplayWidth, color);
    leftEye->drawFastHLine(0, tftDisplayHeight - position, tftDisplayWidth, color);
    rightEye->drawFastHLine(0, tftDisplayHeight - position, tftDisplayWidth, color);

    while (currentMillis - previousMillis < blinkDelay) {
      currentMillis = millis();
    }
    previousMillis = currentMillis;
  }
}

void focusEyes(uint16_t color) {
  Serial.println(F("focusEyes"));

  for (uint16_t step = 0; step <= ((tftDisplayHeight / 2) / 6 * 4); step++) {

    leftEye->drawFastHLine(0, step, tftDisplayWidth, color);
    rightEye->drawFastHLine(0, step, tftDisplayWidth, color);
    leftEye->drawFastHLine(0, tftDisplayHeight - step, tftDisplayWidth, color);
    rightEye->drawFastHLine(0, tftDisplayHeight - step, tftDisplayWidth, color);

    while (currentMillis - previousMillis < blinkDelay) {
      currentMillis = millis();
    }
    previousMillis = currentMillis;
  }
}

void sadEyes(uint16_t color) {
  Serial.println(F("sadEyes"));

  uint16_t length = tftDisplayHeight;

  for (uint16_t step = 0; step <= tftDisplayHeight; step++) {

    leftEye->drawFastHLine(tftDisplayHeight - length, tftDisplayHeight - step, length, color);
    rightEye->drawFastHLine(0, tftDisplayHeight - step, length, color);
    length = length - 2;

    while (currentMillis - previousMillis < blinkDelay) {
      currentMillis = millis();
    }
    previousMillis = currentMillis;
  }
}

void angryEyes(uint16_t color) {
  Serial.println(F("angryEyes"));

  uint16_t length = tftDisplayHeight;

  for (uint16_t step = 0; step <= tftDisplayHeight; step++) {

    leftEye->drawFastHLine(0, tftDisplayHeight - step, length, color);
    rightEye->drawFastHLine(tftDisplayHeight - length, tftDisplayHeight - step, length, color);
    length = length - 2;

    while (currentMillis - previousMillis < blinkDelay) {
      currentMillis = millis();
    }
    previousMillis = currentMillis;
  }
}

void closeEye(Arduino_GFX *eye, uint16_t color) {
  Serial.println(F("closeEye"));
  for (uint16_t step = 0; step <= tftDisplayHeight / 2; step++) {
    eye->drawFastHLine(0, step, tftDisplayWidth, color);
    eye->drawFastHLine(0, tftDisplayHeight - step, tftDisplayWidth, color);

    while (currentMillis - previousMillis < blinkDelay) {
      currentMillis = millis();
    }
    previousMillis = currentMillis;
  }
}

void openEye(Arduino_GFX *eye, uint16_t color) {
  Serial.println(F("openEye"));

  for (uint16_t step = 0; step <= tftDisplayHeight / 2; step++) {
    uint16_t position = (tftDisplayHeight / 2) - step;

    eye->drawFastHLine(0, position, tftDisplayWidth, color);
    eye->drawFastHLine(0, tftDisplayHeight - position, tftDisplayWidth, color);

    while (currentMillis - previousMillis < blinkDelay) {
      currentMillis = millis();
    }
    previousMillis = currentMillis;
  }
}

void focusEye(Arduino_GFX *eye, uint16_t color) {
  Serial.println(F("focusEye"));

  for (uint16_t step = 0; step <= ((tftDisplayHeight / 2) / 6 * 4); step++) {
    eye->drawFastHLine(0, step, tftDisplayWidth, color);
    eye->drawFastHLine(0, tftDisplayHeight - step, tftDisplayWidth, color);

    while (currentMillis - previousMillis < blinkDelay) {
      currentMillis = millis();
    }
    previousMillis = currentMillis;
  }
}

void sadEye(Arduino_GFX *eye, bool inner, uint16_t color) {
  Serial.println(F("sadEye"));
  uint16_t length = tftDisplayHeight;
  uint16_t left = 0;

  for (uint16_t step = 0; step <= tftDisplayHeight; step++) {

    if (inner == true) {
      left = tftDisplayHeight - length;
    }

    eye->drawFastHLine(left, tftDisplayHeight - step, length, color);

    length = length - 2;

    while (currentMillis - previousMillis < blinkDelay) {
      currentMillis = millis();
    }
    previousMillis = currentMillis;
  }
}

void openEyesLoop() {
  if ((leftEyeTargetState == Open || leftEyeTargetState == Blink) || (rightEyeTargetState == Open || rightEyeTargetState == Blink)) {

    if ((leftEyeTargetState == Open || leftEyeTargetState == Blink) && leftEyeState != Open && (rightEyeTargetState == Open || rightEyeTargetState == Blink) && rightEyeState != Open) {
      openEyes(huyangEyeColor);
      leftEyeState = Open;
      rightEyeState = Open;
    } else if ((leftEyeTargetState == Open || leftEyeTargetState == Blink) && leftEyeState != Open) {
      openEye(leftEye, huyangEyeColor);
      leftEyeState = Open;
    } else if ((rightEyeTargetState == Open || rightEyeTargetState == Blink) && rightEyeState != Open) {
      openEye(rightEye, huyangEyeColor);
      rightEyeState = Open;
    }

    if (leftEyeTargetState == Blink) {
      leftEyeTargetState = Open;
    }
    if (rightEyeTargetState == Blink) {
      rightEyeTargetState = Open;
    }
  }
}

void closeEyesLoop() {
  if (currentMillis - previousMillis > randomDuration) {

    if ((leftEyeTargetState == Closed || leftEyeTargetState == Blink) || (rightEyeTargetState == Closed || rightEyeTargetState == Blink)) {

      if ((leftEyeTargetState == Closed || leftEyeTargetState == Blink) && leftEyeState != Closed && (rightEyeTargetState == Closed || rightEyeTargetState == Blink) && rightEyeState != Closed) {
        closeEyes(huyangClosedEyeColor);
        leftEyeState = Closed;
        rightEyeState = Closed;
      } else if ((leftEyeTargetState == Closed || leftEyeTargetState == Blink) && leftEyeState != Closed) {
        closeEye(leftEye, huyangClosedEyeColor);
        leftEyeState = Closed;
      } else if ((rightEyeTargetState == Closed || rightEyeTargetState == Blink) && rightEyeState != Closed) {
        closeEye(rightEye, huyangClosedEyeColor);
        rightEyeState = Closed;
      }
    }
  }
}

void focusEyesLoop() {
  if (leftEyeTargetState == Focus || rightEyeTargetState == Focus) {
    if ((leftEyeTargetState == Focus && leftEyeState != Focus) && (rightEyeTargetState == Focus && rightEyeState != Focus)) {
      focusEyes(huyangClosedEyeColor);
      leftEyeState = Focus;
      rightEyeState = Focus;
    } else if (leftEyeTargetState == Focus && leftEyeState != Focus) {
      focusEye(leftEye, huyangClosedEyeColor);
      leftEyeState = Focus;
    } else if (rightEyeTargetState == Focus && rightEyeState != Focus) {
      focusEye(rightEye, huyangClosedEyeColor);
      rightEyeState = Focus;
    }
  }
}

void sadEyesLoop() {
  if (leftEyeTargetState == Sad || rightEyeTargetState == Sad) {
    if ((leftEyeTargetState == Sad && leftEyeState != Sad) && (rightEyeTargetState == Sad && rightEyeState != Sad)) {
      sadEyes(huyangClosedEyeColor);
      leftEyeState = Sad;
      rightEyeState = Sad;
    } else if (leftEyeTargetState == Sad && leftEyeState != Sad) {
      sadEye(leftEye, true, huyangClosedEyeColor);
      leftEyeState = Sad;
    } else if (rightEyeTargetState == Sad && rightEyeState != Sad) {
      sadEye(rightEye, false, huyangClosedEyeColor);
      rightEyeState = Sad;
    }
  }
}

void angryEyesLoop() {
  if (leftEyeTargetState == Angry || rightEyeTargetState == Angry) {

    if ((leftEyeTargetState == Angry && leftEyeState != Angry) && (rightEyeTargetState == Angry && rightEyeState != Angry)) {
      angryEyes(huyangClosedEyeColor);
      leftEyeState = Angry;
      rightEyeState = Angry;
    } else if (leftEyeTargetState == Angry && leftEyeState != Angry) {
      sadEye(leftEye, false, huyangClosedEyeColor);
      leftEyeState = Angry;
    } else if (rightEyeTargetState == Angry && rightEyeState != Angry) {
      sadEye(rightEye, true, huyangClosedEyeColor);
      rightEyeState = Angry;
    }
  }
}

void setupEyes() {
  leftEye->begin();
  rightEye->begin();

  leftEye->fillScreen(huyangEyeColor);
  rightEye->fillScreen(huyangEyeColor);

  delay(500);
}

void loopEyes() {
  closeEyesLoop();

  if (currentMillis - previousMillis > 100) {

    openEyesLoop();
    focusEyesLoop();
    sadEyesLoop();
    angryEyesLoop();


    if (leftEyeState == Blink) {
      leftEyeState = Open;
    }

    if (rightEyeState == Blink) {
      rightEyeState = Open;
    }
  }

  if (automaticState == AutomaticOn) {
    randomDuration = random(6, 12 + 1) * 1000;
    leftEyeTargetState = Blink;
    rightEyeTargetState = Blink;
  }
}