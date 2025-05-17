#ifndef DMXInterface_H
#define DMXInterface_H

#include <DmxSimple.h>
#include <stdint.h>

class DMXInterface {
  public:
    DMXInterface(uint8_t txPin, uint16_t numChan);
    void initDmxChannels();
    void setBrightness(uint8_t brightness);
    void writeDMX(uint8_t channel, uint8_t value);
    void zeroBrightness();
  private:
    uint16_t numChannels;
};

#endif