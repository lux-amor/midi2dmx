#ifndef EFFECT_INTERFACE_H
#define EFFECT_INTERFACE_H

#include <Arduino.h>
#include "dmx_interface.h"
#include <stdint.h>

#define NUM_LAMPS 5

class EffectInterface {
  public:
    EffectInterface(DMXInterface* dmx) : dmxInterface(dmx) {};
    ~EffectInterface();
    virtual void update();
    void setPitchBendOffset(int bend);
    void start(byte note, byte velocity);
    void stop();

  protected:
    const uint8_t numLamps = NUM_LAMPS;
    uint8_t brightness = 0;
    bool* currentMask = nullptr;
    unsigned long updateInterval = 200.0; //ms
    virtual void onUpdate() = 0;
    virtual void onStart(byte note, byte velocity) = 0;
    virtual void onStop() {};
    void updateLights(uint8_t brightnessOffset);

  private:
    DMXInterface* dmxInterface;
    bool active = false;
    int8_t pitchBendOffset = 0;
    unsigned long previousMillis = 0;
    uint8_t getValidBrightness(uint8_t brightness, unsigned long delta, int8_t offset);

};

#endif