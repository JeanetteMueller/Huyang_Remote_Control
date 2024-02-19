
void closeEyes(uint16_t color) {
  Serial.println(F("closeEyes"));

  leftEyeOpen = false;
  rightEyeOpen = false;

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
  leftEyeOpen = true;
  rightEyeOpen = true;
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
  if ((leftEyeState == Open || leftEyeState == Blink) && (rightEyeState == Open || rightEyeState == Blink)) {
    openEyes(huyangEyeColor);
  } else if (leftEyeState == Open || leftEyeState == Blink) {
    openEye(leftEye, huyangEyeColor);
    leftEyeOpen = true;
  } else if (rightEyeState == Open || rightEyeState == Blink) {
    openEye(rightEye, huyangEyeColor);
    rightEyeOpen = true;
  }
}

void closeEyesLoop() {
  if (currentMillis - previousMillis > randomDuration) {
    if (leftEyeOpen && rightEyeOpen && (leftEyeState == Closed || leftEyeState == Blink) && (rightEyeState == Closed || rightEyeState == Blink)) {
      closeEyes(huyangClosedEyeColor);
    } else if (leftEyeOpen && (leftEyeState == Closed || leftEyeState == Blink)) {
      closeEye(leftEye, huyangClosedEyeColor);
      leftEyeOpen = false;
    } else if (rightEyeOpen && (rightEyeState == Closed || rightEyeState == Blink)) {
      closeEye(rightEye, huyangClosedEyeColor);
      rightEyeOpen = false;
    }
  }
}

void focusEyesLoop() {
  if (leftEyeState == Focus || rightEyeState == Focus) {
    if (leftEyeState == Focus && rightEyeState == Focus) {
      focusEyes(huyangClosedEyeColor);
    } else if (leftEyeState == Focus) {
      focusEye(leftEye, huyangClosedEyeColor);
      leftEyeOpen = false;
    } else if (rightEyeState == Focus) {
      focusEye(rightEye, huyangClosedEyeColor);
      rightEyeOpen = false;
    }
  }
}

void sadEyesLoop() {
  if (leftEyeState == Sad || rightEyeState == Sad) {
    if (leftEyeState == Sad && rightEyeState == Sad) {
      sadEyes(huyangClosedEyeColor);
    } else if (leftEyeState == Sad) {
      sadEye(leftEye, true, huyangClosedEyeColor);
    } else if (rightEyeState == Sad) {
      sadEye(rightEye, false, huyangClosedEyeColor);
    }
  }
}

void angryEyesLoop() {
  if (leftEyeState == Angry || rightEyeState == Angry) {
    if (leftEyeState == Angry && rightEyeState == Angry) {
      angryEyes(huyangClosedEyeColor);
    } else if (leftEyeState == Angry) {
      sadEye(leftEye, false, huyangClosedEyeColor);
    } else if (rightEyeState == Angry) {
      sadEye(rightEye, true, huyangClosedEyeColor);
    }
  }
}

void setupEyes() {
  leftEye->begin();
  rightEye->begin();

  closeEyes(huyangClosedEyeColor);

  delay(1000);

  openEyes(huyangEyeColor);

  delay(2000);
}

void loopEyes() {
  closeEyesLoop();

  if (currentMillis - previousMillis > 100) {
    if (!leftEyeOpen || !rightEyeOpen) {
      openEyesLoop();
    } else {
      focusEyesLoop();
      sadEyesLoop();
      angryEyesLoop();
    }

    if (leftEyeState == Blink) {
      leftEyeState = Open;
    }

    if (rightEyeState == Blink) {
      rightEyeState = Open;
    }
  }

  if (automaticState == AutomaticOn) {
    randomDuration = random(4, 12 + 1) * 1000;
    leftEyeState = Blink;
    rightEyeState = Blink;
  }
}