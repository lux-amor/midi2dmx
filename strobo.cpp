#include "strobo.h"

void Strobo::onStart(byte note, byte velocity) {
  brightness = min(255, max(0, 2*(note + 1)));
  updateInterval = (127 - velocity) * 2.5;
  #ifdef ENABLE_SERIAL_DEBUG
    Serial.print("triggered strobo with brightness: ");
    Serial.print(brightness);
    Serial.print(" and interval: ");
    Serial.println(updateInterval);
  #endif
}

void Strobo::onUpdate() {
  if (currentPattern == nullptr) {
    #ifdef ENABLE_SERIAL_DEBUG
      Serial.print("Invalid pattern pointer for strobo fx");
    #endif
    return;
  } else {
    setMask(currentPattern[currentStep]);
  }

  updateLights(0);

  currentStep++;
  if (currentStep >= currentPatternRows) {
    currentStep = 0;
  }
}