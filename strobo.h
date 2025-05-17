#ifndef STROBO_H
#define STROBO_H

#include "config.h"
#include "effect_interface.h"

class Strobo : public EffectInterface {
  public:
    Strobo(DMXInterface* dmx) : EffectInterface(dmx) {};

    template <size_t N>
    void Strobo::setPattern(const bool (&pattern)[N][NUM_LAMPS]) {
      currentPattern = pattern;
      currentPatternRows = N;
      currentStep = 0;
    }

  protected:
    virtual void onStart(byte note, byte velocity);
    virtual void onUpdate();

  private:
    const bool (*currentPattern)[NUM_LAMPS] = nullptr;
    int currentStep = 0;
    int currentPatternRows = 0;
};

#endif
