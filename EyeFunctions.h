
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
  if ((leftEyeTargetState == Open || leftEyeTargetState == Blink) && (rightEyeTargetState == Open || rightEyeTargetState == Blink)) {
    if (leftEyeState != Open && rightEyeState != Open) {
      openEyes(huyangEyeColor);
      leftEyeState = leftEyeTargetState;
      rightEyeState = rightEyeTargetState;
    } else if (leftEyeState != Open) {
      openEye(leftEye, huyangEyeColor);
      leftEyeState = leftEyeTargetState;
    } else if (rightEyeState != Open) {
      openEye(rightEye, huyangEyeColor);
      rightEyeState = rightEyeTargetState;
    }
  }
}

void closeEyesLoop() {
  if (currentMillis - previousMillis > randomDuration) {

    if ((leftEyeTargetState == Closed || leftEyeTargetState == Blink) || (rightEyeTargetState == Closed || rightEyeTargetState == Blink)) {
      if (leftEyeState != Closed && rightEyeState != Closed) {
        closeEyes(huyangClosedEyeColor);
        leftEyeState = leftEyeTargetState;
        rightEyeState = rightEyeTargetState;
      } else if (leftEyeState != Closed) {
        closeEye(leftEye, huyangClosedEyeColor);
        leftEyeState = leftEyeTargetState;
      } else if (rightEyeState != Closed) {
        closeEye(rightEye, huyangClosedEyeColor);
        rightEyeState = rightEyeTargetState;
      }
    }
  }
}

void focusEyesLoop() {
  if (leftEyeTargetState == Focus || rightEyeTargetState == Focus) {
    if (leftEyeState != Focus && rightEyeState != Focus) {
      focusEyes(huyangClosedEyeColor);
      leftEyeState = Focus;
      rightEyeState = Focus;
    } else if (leftEyeState == Focus) {
      focusEye(leftEye, huyangClosedEyeColor);
      leftEyeState = Focus;
    } else if (rightEyeState == Focus) {
      focusEye(rightEye, huyangClosedEyeColor);
      rightEyeState = Focus;
    }
  }
}

void sadEyesLoop() {
  if (leftEyeTargetState == Sad || rightEyeTargetState == Sad) {
    if (leftEyeState != Sad && rightEyeState != Sad) {
      sadEyes(huyangClosedEyeColor);
      leftEyeState = Sad;
      rightEyeState = Sad;
    } else if (leftEyeState == Sad) {
      sadEye(leftEye, true, huyangClosedEyeColor);
      leftEyeState = Sad;
    } else if (rightEyeState == Sad) {
      sadEye(rightEye, false, huyangClosedEyeColor);
      rightEyeState = Sad;
    }
  }
}

void angryEyesLoop() {
  if (leftEyeTargetState == Angry || rightEyeTargetState == Angry) {

    if (leftEyeState != Angry && rightEyeState != Angry) {
      angryEyes(huyangClosedEyeColor);
      leftEyeState = Angry;
      rightEyeState = Angry;
    } else if (leftEyeState != Angry) {
      sadEye(leftEye, false, huyangClosedEyeColor);
      leftEyeState = Angry;
    } else if (rightEyeState != Angry) {
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
    leftEyeState = Open;
    leftEyeTargetState = Blink;
    rightEyeState = Open;
    rightEyeTargetState = Blink;
  }
}