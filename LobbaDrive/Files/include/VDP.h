#ifndef VDP_H
#define VDP_H

#include <vector>
#include <cstdint>
#include <SDL2/SDL.h>  // Required for SDL2 rendering

class VDP {
public:
    // Constructor and Destructor
    VDP();
    ~VDP();

    // Initializes the VDP, sets default settings
    void initialize();

    // Emulates a VDP cycle (called every frame)
    void emulateCycle();

    // Load a tile map (for backgrounds)
    void loadTileMap(const std::vector<uint8_t>& tiles);

    // Load sprite data (for sprites rendering)
    void loadSprites(const std::vector<uint8_t>& sprites);

    // Set the VDP control register (this manages VDP mode settings)
    void setControlRegister(uint8_t value);

    // Set the VDP data register (this sets data like tile maps)
    void setDataRegister(uint8_t value);

    // Get the VDP status register (returns the current status of VDP)
    uint8_t getStatusRegister() const;

    // Render a frame (this should be called once per frame)
    void renderFrame(SDL_Renderer* renderer);

private:
    // Video memory for VDP (both background and sprite memory)
    std::vector<uint8_t> vdpMemory;

    // VDP registers
    uint8_t controlRegister;  // Control register for video mode settings
    uint8_t dataRegister;     // Data register (tile data, etc.)

    // Tile and sprite data storage
    std::vector<uint8_t> tileMap;
    std::vector<uint8_t> sprites;

    // Helper functions
    void renderBackground(SDL_Renderer* renderer);
    void renderSprites(SDL_Renderer* renderer);

    // Simulation of the screen buffer (for now, just a placeholder)
    std::vector<uint8_t> screenBuffer;

    // Video output dimensions (usually 320x224 for Sega Genesis)
    const int screenWidth = 320;
    const int screenHeight = 224;
};

#endif  // VDP_H
