#ifndef FADEOUT_H
#define FADEOUT_H

#include "config.h"
#include "effect_interface.h"
#include <math.h>

class FadeOut : public EffectInterface {
  public:
    FadeOut(DMXInterface* dmx) : EffectInterface(dmx) {};

    template <size_t N>
    void FadeOut::setMask(const bool (&values)[N]) {
        static_assert(N > 0, "Mask cannot be empty");
        memcpy(currentMask, values, N * sizeof(bool));
    }

  protected:
    virtual void onStart(byte note, byte velocity);
    virtual void onUpdate();

  private:
    const float fadeUpdateInterval = 5.0; //ms
    const float fadeTimeFactor = 0.04;
    float brightnessDelta = 0;
};
#endif