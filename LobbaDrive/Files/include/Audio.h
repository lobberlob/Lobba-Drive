#ifndef AUDIO_H
#define AUDIO_H

#include <cstdint>
#include <vector>
#include <iostream>

class Audio {
public:
    Audio();
    ~Audio();

    // Initialize the audio system
    void initialize();

    // Emulate one audio frame (called once per frame)
    void emulateCycle();

    // Set audio register values
    void setRegister(uint8_t reg, uint8_t value);

    // Render audio to a buffer (for now, just to simulate sound)
    void renderAudio();

    // Get the current sample output (this would be sent to the sound hardware in a real emulator)
    std::vector<int16_t>& getAudioBuffer();

private:
    // Audio registers (this is a simplified version, actual PSG has more registers)
    uint8_t registers[0x20];  // The Yamaha 2612 has 32 registers to control sound
    std::vector<int16_t> audioBuffer;  // Audio buffer for output sound

    // FM synthesis channel states
    struct Channel {
        int frequency;
        int volume;
        bool active;
    };

    Channel channels[6];  // There are 6 FM channels on the Genesis

    // Helper functions for FM synthesis
    void updateFMChannels();
    void mixAudio();
};

#endif  // AUDIO_H
