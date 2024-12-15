#include "Audio.h"
#include <cstring>

Audio::Audio() {
    // Initialize the registers and channels
    std::memset(registers, 0, sizeof(registers));  // Clear all registers
    std::memset(channels, 0, sizeof(channels));    // Clear all channels
    audioBuffer.resize(44100);  // For example, allocate a buffer for 1 second of audio at 44.1kHz
}

Audio::~Audio() {
    // Cleanup resources (not much to clean up in this case)
}

void Audio::initialize() {
    // Reset registers and channels to default state
    std::memset(registers, 0, sizeof(registers));
    std::memset(channels, 0, sizeof(channels));
    audioBuffer.clear();
    audioBuffer.resize(44100);  // Allocate 1 second of audio buffer (at 44.1kHz)
}

void Audio::emulateCycle() {
    // Simulate one audio frame (typically this would be called every frame)
    updateFMChannels();  // Update the FM channels based on current register values
    mixAudio();          // Mix the audio from the channels into the audio buffer
}

void Audio::setRegister(uint8_t reg, uint8_t value) {
    // This function sets the audio register (you would need to implement the actual FM chip behavior)
    if (reg < 0x20) {
        registers[reg] = value;
        std::cout << "Audio register " << std::hex << (int)reg << " set to " << std::hex << (int)value << std::endl;
    }
}

void Audio::renderAudio() {
    // For now, just simulate audio output by printing the buffer values
    std::cout << "Rendering audio output: " << std::endl;
    for (size_t i = 0; i < audioBuffer.size(); ++i) {
        std::cout << audioBuffer[i] << " ";  // This would typically be output to a sound device
    }
}

std::vector<int16_t>& Audio::getAudioBuffer() {
    return audioBuffer;
}

void Audio::updateFMChannels() {
    // Update the state of the FM channels based on registers and frequency/volume settings
    for (int i = 0; i < 6; ++i) {
        // In a real implementation, we'd use the registers to determine the frequency, volume, and state of the channel.
        // For now, just simulate some simple values for each channel.
        if (channels[i].active) {
            channels[i].frequency = 440;  // Simulate a sine wave at 440Hz (A4 note)
            channels[i].volume = 128;     // Simulate a medium volume
        }
    }
}

void Audio::mixAudio() {
    // Mix the audio from each active FM channel into the audio buffer
    for (size_t i = 0; i < audioBuffer.size(); ++i) {
        int16_t sample = 0;

        // Simple mixing: add the contributions of each active FM channel
        for (int j = 0; j < 6; ++j) {
            if (channels[j].active) {
                // Here we simulate the channel's sound as a simple sine wave (for demonstration purposes)
                // A real implementation would use a proper wave generation algorithm (FM synthesis, PCM, etc.)
                sample += static_cast<int16_t>((channels[j].volume * sin(2.0 * M_PI * channels[j].frequency * i / 44100.0)));
            }
        }

        // Store the mixed sample in the buffer
        audioBuffer[i] = sample;
    }
}
