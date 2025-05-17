#ifndef STROBO_H
#define STROBO_H

#include "config.h"
#include "effect_interface.h"

class Strobo : public EffectInterface {
  public:
    Strobo(DMXInterface* dmx) : EffectInterface(dmx) {};
    void handleStrobo();
    void setStrobo(uint8_t brightness, bool state, int interval);

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

//TODO move patterns to seperate lamp specific file. include depending on NUM_LAMPS definition
const bool chaserPattern[5][NUM_LAMPS] = {
  { 1, 0, 0, 0, 0 },
  { 0, 1, 0, 0, 0 },
  { 0, 0, 1, 0, 0 },
  { 0, 0, 0, 1, 0 },
  { 0, 0, 0, 0, 1 }
};

const bool changerPattern[2][NUM_LAMPS] = {
  { 1, 0, 1, 0, 1 },
  { 0, 1, 0, 1, 0 }
};

const bool stroboPattern[2][NUM_LAMPS] = {
  { 1, 1, 1, 1, 1 },
  { 0, 0, 0, 0, 0 }
};

const bool alternatePattern[2][NUM_LAMPS] = {
  { 1, 1, 1, 0, 0 },
  { 0, 0, 1, 1, 1 }
};

const bool runnerPattern[6][NUM_LAMPS] = {
  { 1, 0, 0, 0, 0 },
  { 1, 1, 0, 0, 0 },
  { 0, 1, 1, 0, 0 },
  { 0, 0, 1, 1, 0 },
  { 0, 0, 0, 1, 1 },
  { 0, 0, 0, 0, 1 }
};

#endif
