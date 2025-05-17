#include "dmx_interface.h"

DMXInterface::DMXInterface(uint8_t txPin, uint16_t numChan) {
  numChannels = numChan;
  DmxSimple.usePin(txPin);
  DmxSimple.maxChannel(numChan);
  initDmxChannels();
}

void DMXInterface::initDmxChannels() {
  zeroBrightness();
}

void DMXInterface::setBrightness(uint8_t brightness) {
  for (int channel = 1; channel <= numChannels; ++channel) {
    writeDMX(channel, brightness);
  }
}

void DMXInterface::writeDMX(uint8_t channel, uint8_t value) {
  #ifdef OUTPUT_DMX_VALUES
    Serial.println("writing DMX values");
    Serial.println("channel: ");
    Serial.println(channel);
    Serial.println("value: ");
    Serial.println(value);
  #endif
  DmxSimple.write(channel, value);
}

void DMXInterface::zeroBrightness() {
  setBrightness(0);
}