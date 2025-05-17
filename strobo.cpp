#include "strobo.h"

Strobo::Strobo(DMXInterface* dmx) : EffectInterface(dmx) {}

void Strobo::onStart(byte note, byte velocity) {
  brightness = min(255, max(0, 2*(note + 1)));
  float interval = (127 - velocity) * 2.5;
  #ifdef ENABLE_SERIAL_DEBUG
    Serial.print("triggered strobo with brightness: ");
    Serial.print(brightness);
    Serial.print(" and interval: ");
    Serial.println(interval);
  #endif
  brightness = brightness;
  updateInterval = interval;
}

void Strobo::onUpdate() {
  if (currentPattern == nullptr) {
    #ifdef ENABLE_SERIAL_DEBUG
      Serial.print("Invalid pattern pointer for strobo fx");
    #endif
    return;
  } else {
    currentMask = currentPattern[currentStep];
  }

  updateLights(0);

  currentStep++;
  if (currentStep >= currentPatternRows) {
    currentStep = 0;
  }
}