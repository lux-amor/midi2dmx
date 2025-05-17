#ifndef FADEIN_H
#define FADEIN_H

#include "config.h"
#include "effect_interface.h"
#include <math.h>

class FadeIn : public EffectInterface {
  public:
    FadeIn(DMXInterface* dmx) : EffectInterface(dmx) {};

  protected:
    virtual void onStart(byte note, byte velocity);
    virtual void onUpdate();

  private:
    const float fadeTimeFactor = 0.5;
    float brightnessDelta = 0;
};
#endif