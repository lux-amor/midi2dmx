#ifndef FADEIN_H
#define FADEIN_H

#include "effect_interface.h"
#include <math.h>

#define NUM_LAMPS 5

class FadeIn : public EffectInterface {
  public:
    FadeIn(DMXInterface* dmx);

    template <size_t N>
    void FadeIn::setMask(const bool (&values)[N]) {
        static_assert(N > 0, "Mask cannot be empty");
        memcpy(currentMask, values, N * sizeof(bool));
    }

  protected:
    virtual void onStart(byte note, byte velocity);
    virtual void onUpdate();

  private:
    const float fadeUpdateInterval = 5.0; //ms
    const float fadeTimeFactor = 25.0;
    float brightnessDelta = 0;
};
#endif