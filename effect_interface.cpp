#include "effect_interface.h"

EffectInterface::~EffectInterface() {
  delete[] currentMask;
}

uint8_t EffectInterface::getValidBrightness(uint8_t brightness, unsigned long delta, int8_t offset) {
  int actualBrightness = (int)brightness + delta + offset; 
  if (actualBrightness <= 0) {
    #ifdef ENABLE_SERIAL_DEBUG
      Serial.println(F("Limit brightness to 0"));
    #endif
    actualBrightness = 0;
  } else if (actualBrightness >= 255) {
    #ifdef ENABLE_SERIAL_DEBUG
      Serial.println(F("Limit brightness to 255"));
    #endif
    actualBrightness = 255;
  }
  return actualBrightness;
}

void EffectInterface::setPitchBendOffset(int bend) {
  pitchBendOffset = bend / 8192.0f * 100;
}

void EffectInterface::start(byte note, byte velocity) {
    active = true;
    onStart(note, velocity);
}

void EffectInterface::stop() {
    active = false;
    brightness = 0;
    onStop();
}

void EffectInterface::update() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= updateInterval) {
    previousMillis = currentMillis;
    if (active) {
      onUpdate();
    }
  }
}

void EffectInterface::updateLights(uint8_t brightnessOffset) {
  if (currentMask != nullptr) {
    uint8_t actualBrightness = getValidBrightness(brightness, brightnessOffset, pitchBendOffset); 
    #ifdef ENABLE_SERIAL_DEBUG
      Serial.print("writing actual brightness: ");
      Serial.println(actualBrightness);
    #endif
    for (int i = 0; i < numLamps; i++) {
      dmxInterface->writeDMX(i + 1, currentMask[i] ? actualBrightness : 0);
    }
  }
}