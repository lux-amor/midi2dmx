/*** DOCS ***/
/*
  Midi Settings: In Ableton Sync must be turned on for Midi Out!

  Strobo:
    - Velocity => frequency
    - Note => Brigness
    - Pitch Bend => Brightness Offset

  FadeIn:
    - Velocity => Speed
    - Note => Initial Brightness
    - Pitchbend => Brightness Offset

  FadeOut:
    - Velocity => Speed
    - Note => Initial Brightness
    - Pitchbend => Brightness Offset
*/

//#define ENABLE_SERIAL_DEBUG
//#define OUTPUT_DMX_VALUES

#define DMX_TX_PIN 1    // Transmit pin, connect to DI of MAX485 module
#define DMX_DE_PIN 9    // Enable pin, connect to DE+RE of MAX485 module
#define DMX_NUM_CHAN 5  // Number of DMX channels to use, maximum is 512 (if sufficient RAM)
#define MIDI_CHANNEL MIDI_CHANNEL_OMNI

#include "dmx_interface.h"
#include "fade_in.h"
#include "fade_out.h"
#include "strobo.h"
#include <USB-MIDI.h>
typedef USBMIDI_NAMESPACE::usbMidiTransport __umt;
typedef MIDI_NAMESPACE::MidiInterface<__umt> __ss;
__umt usbMIDI(0);
__ss MIDICoreUSB((__umt&)usbMIDI);

DMXInterface dmx(DMX_TX_PIN, DMX_NUM_CHAN);
FadeIn fadeIn(&dmx);
FadeOut fadeOut(&dmx);
Strobo strobo(&dmx);

void setup() {
  #ifdef ENABLE_SERIAL_DEBUG
    Serial.begin(115200);
  #endif

  pinMode(DMX_DE_PIN, OUTPUT);
  digitalWrite(DMX_DE_PIN, HIGH);

  MIDICoreUSB.setHandleNoteOn(OnNoteOn);
  MIDICoreUSB.setHandleNoteOff(OnNoteOff);
  MIDICoreUSB.setHandlePitchBend(OnPitchBend);
  // MIDICoreUSB.setHandleClock(OnClock); //TODO synced strobo would be amazing!
  MIDICoreUSB.setHandleStop(OnStop);
  MIDICoreUSB.begin(MIDI_CHANNEL);
}

void loop() {
  MIDICoreUSB.read();
  fadeIn.update();
  fadeOut.update();
  strobo.update();
}

static void OnNoteOn(byte channel, byte note, byte velocity) {
  #ifdef ENABLE_SERIAL_DEBUG
    Serial.print(F("NoteOn  from channel: "));
    Serial.print(channel);
    Serial.print(F(", note: "));
    Serial.print(note);
    Serial.print(F(", velocity: "));
    Serial.println(velocity);
  #endif

  if (channel == 1) {
    const bool defaultMask[5] = {1, 1, 1, 1, 1};
    fadeIn.setMask(defaultMask);
    fadeIn.start(note, velocity);
  }

  if (channel == 2) {
    const bool defaultMask[5] = {1, 1, 1, 1, 1};
    fadeOut.setMask(defaultMask);
    fadeOut.start(note, velocity);
  }

  if (channel == 3) {
    #ifdef ENABLE_SERIAL_DEBUG
        Serial.println(F("Set strobo to chaser"));
    #endif
    strobo.setPattern(chaserPattern);
    strobo.start(note, velocity);
  }

  if (channel == 4) {
    #ifdef ENABLE_SERIAL_DEBUG
        Serial.println(F("Set strobo to changer"));
    #endif
    strobo.setPattern(changerPattern);
    strobo.start(note, velocity);
  }

  if (channel == 5) {
    #ifdef ENABLE_SERIAL_DEBUG
        Serial.println(F("Set strobo to strobo"));
    #endif
    strobo.setPattern(stroboPattern);
    strobo.start(note, velocity);
  }

  if (channel == 6) {
    #ifdef ENABLE_SERIAL_DEBUG
        Serial.println(F("Set strobo to alternate"));
    #endif
    strobo.setPattern(alternatePattern);
    strobo.start(note, velocity);
  }
  if (channel == 7) {
    #ifdef ENABLE_SERIAL_DEBUG
        Serial.println(F("Set strobo to runner"));
    #endif
    strobo.setPattern(runnerPattern);
    strobo.start(note, velocity);
  }

  if (channel == 15) {
    const bool leftMask[5] = {1, 1, 1, 0, 0};
    fadeOut.setMask(leftMask);
    fadeOut.start(note, velocity);
  }
  if (channel == 16) {
    const bool rightMask[5] = {0, 0, 1, 1, 1};
    fadeOut.setMask(rightMask);
    fadeOut.start(note, velocity);
  }
}

static void OnNoteOff(byte channel, byte note, byte velocity) {
  #ifdef ENABLE_SERIAL_DEBUG
    Serial.print(F("NoteOff from channel: "));
    Serial.print(channel);
    Serial.print(F(", note: "));
    Serial.print(note);
    Serial.print(F(", velocity: "));
    Serial.println(velocity);
  #endif

  if (channel == 1) {
    fadeIn.stop();
  } else if (channel == 2 || channel == 15 || channel == 16) {
    fadeOut.stop();
  } else {
    strobo.stop();
  }
  dmx.zeroBrightness();
}

static void OnStop() {
  #ifdef ENABLE_SERIAL_DEBUG
    Serial.println(F("Stop"));
  #endif
  strobo.stop();
  fadeIn.stop();
  fadeOut.stop();
  dmx.zeroBrightness();
}

static void OnPitchBend(byte channel, int bend) {
  #ifdef ENABLE_SERIAL_DEBUG
    Serial.print(F("PitchBend from channel: "));
    Serial.print(channel);
    Serial.print(F(", bend: "));
    Serial.println(bend);
  #endif
  if (channel == 1 ) {
    fadeIn.setPitchBendOffset(bend);
  } else if (channel == 2 || channel == 15 || channel == 16 )  {
    fadeOut.setPitchBendOffset(bend);
  } else {
    strobo.setPitchBendOffset(bend);
  }
}