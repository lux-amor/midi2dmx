#include "effect_interface.h"

uint8_t EffectInterface::getValidBrightness(float brightness, float delta, int8_t offset) {
  #ifdef ENABLE_SERIAL_DEBUG
    Serial.println("Calculating valid brightness for:");
    Serial.print("brightness: ");
    Serial.println(brightness);
    Serial.print("brightness delta: ");
    Serial.println(delta);
    Serial.print("pitchbend offset: ");
    Serial.println(offset);
  #endif
  float actualBrightness = brightness + delta + offset; 
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
  return ceil(actualBrightness);
}

void EffectInterface::setMask(const bool (&values)[NUM_LAMPS]) {
    static_assert(NUM_LAMPS > 0, "Mask cannot be empty");
    memcpy(currentMask, values, NUM_LAMPS * sizeof(bool));
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

void EffectInterface::updateLights(float brightnessOffset) {
  if (currentMask != nullptr) {
    uint8_t actualBrightness = getValidBrightness(brightness, brightnessOffset, pitchBendOffset); 
    #ifdef ENABLE_SERIAL_DEBUG
      Serial.print("writing actual brightness: ");
      Serial.println(actualBrightness);
    #endif
    for (int i = 0; i < NUM_LAMPS; i++) { // ~24-30 us
      dmxInterface->writeDMX(i + 1, currentMask[i] ? actualBrightness : 0);
    }
  }
}