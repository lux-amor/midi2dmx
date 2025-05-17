#include "fade_in.h"

FadeIn::FadeIn(DMXInterface* dmx) : EffectInterface(dmx) {
  currentMask = new bool[NUM_LAMPS];
  const bool initMask[5] = {1, 1, 1, 1, 1};
  setMask(initMask);
}

void FadeIn::onStart(byte note, byte velocity) {
  brightness = min(255, max(0, 2*(note + 1)));
  float duration = pow(velocity/8.0, 2.0) * fadeTimeFactor;
  
  if (duration != 0) {
    float increments = (float)duration/fadeUpdateInterval;
    brightnessDelta = (float)brightness / ceil(increments);
    #ifdef ENABLE_SERIAL_DEBUG
      Serial.print("triggered FadeIn with a duration of ");
      Serial.println(duration);
      Serial.print("Using ");
      Serial.println(increments);
      Serial.print(" increments with a brightness delta of ");
      Serial.println(brightnessDelta);
    #endif
  }
}

void FadeIn::onUpdate() {
  #ifdef ENABLE_SERIAL_DEBUG
    Serial.print("Updating fadeIn");
  #endif
  updateLights( brightnessDelta );

  if (brightness < 255 - brightnessDelta) {
    brightness += brightnessDelta;
  }
}