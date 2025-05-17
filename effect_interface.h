#ifndef EFFECT_INTERFACE_H
#define EFFECT_INTERFACE_H

#include <Arduino.h>
#include "config.h"
#include "dmx_interface.h"
#include <stdint.h>

class EffectInterface {
  public:
    EffectInterface(DMXInterface* dmx) : dmxInterface(dmx) {};
    virtual void update();
    void setMask(const bool (&values)[NUM_LAMPS]);
    void setPitchBendOffset(int bend);
    void start(byte note, byte velocity);
    void stop();

  protected:
    uint8_t brightness = 0;
    bool currentMask[NUM_LAMPS] = {1};
    unsigned long updateInterval = 200.0; //ms
    virtual void onUpdate() = 0;
    virtual void onStart(byte note, byte velocity) = 0;
    virtual void onStop() {};
    void updateLights(float brightnessOffset);

  private:
    DMXInterface* dmxInterface;
    bool active = false;
    int8_t pitchBendOffset = 0;
    unsigned long previousMillis = 0;
    uint8_t getValidBrightness(uint8_t brightness, float delta, int8_t offset);

};

#endif