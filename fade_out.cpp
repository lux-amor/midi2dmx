#include "fade_out.h"

void FadeOut::onStart(byte note, byte velocity) {
  brightness = min(255, max(0, 2*(note + 1)));
  float duration = velocity * velocity * fadeTimeFactor;
  
  if (duration != 0) {
    float increments = (float)duration/fadeUpdateInterval;
    brightnessDelta = (float)brightness / increments;
    #ifdef ENABLE_SERIAL_DEBUG
      Serial.print("triggered FadeOut with a duration of ");
      Serial.println(duration);
      Serial.print("Setting initial brightness to ");
      Serial.println(brightness);
      Serial.print("Using ");
      Serial.print(increments);
      Serial.print(" increments with a brightness delta of ");
      Serial.println(brightnessDelta);
    #endif
  }
}

void FadeOut::onUpdate() {
  #ifdef ENABLE_SERIAL_DEBUG
    Serial.println("Updating fadeOut");
  #endif
  updateLights( -brightnessDelta );

  if (brightness > brightnessDelta) {
    brightness -= brightnessDelta;
  }
}