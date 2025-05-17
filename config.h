#ifndef CONFIG_H
#define CONFIG_H

#define ENABLE_SERIAL_DEBUG 1
#define OUTPUT_DMX_VALUES   0

#define NUM_LAMPS 5

#define DMX_TX_PIN   1    // Transmit pin, connect to DI of MAX485 module
#define DMX_DE_PIN   9    // Enable pin, connect to DE+RE of MAX485 module
#define DMX_NUM_CHAN 5  // Number of DMX channels to use, maximum is 512 (if sufficient RAM)
#define MIDI_CHANNEL MIDI_CHANNEL_OMNI

#endif