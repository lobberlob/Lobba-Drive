#include "VDP.h"
#include <iostream>
#include <cstring>
#include <SDL2/SDL_image.h>  // Include SDL2_image for texture handling

VDP::VDP()
    : controlRegister(0), dataRegister(0) {
    // Initialize video memory (default size, this will change depending on implementation)
    vdpMemory.resize(0x10000, 0);  // 64 KB of VDP memory (for tilemaps, sprite data, etc.)

    // Initialize screen buffer (just for visualization purposes)
    screenBuffer.resize(screenWidth * screenHeight, 0);  // Placeholder for screen output
}

VDP::~VDP() {
    // Cleanup if necessary
}

void VDP::initialize() {
    // Reset the VDP state to default settings
    controlRegister = 0;
    dataRegister = 0;
    tileMap.clear();
    sprites.clear();
    std::fill(screenBuffer.begin(), screenBuffer.end(), 0);
}

void VDP::emulateCycle() {
    // Each cycle, we will handle the rendering of the screen
    renderBackground();
    renderSprites();
}

void VDP::loadTileMap(const std::vector<uint8_t>& tiles) {
    // Load tile map data into video memory (tile data)
    tileMap = tiles;
}

void VDP::loadSprites(const std::vector<uint8_t>& spritesData) {
    // Load sprite data into memory
    sprites = spritesData;
}

void VDP::setControlRegister(uint8_t value) {
    // This control register changes the VDP mode (screen settings, etc.)
    controlRegister = value;
    std::cout << "VDP Control Register set to: " << std::hex << (int)value << std::endl;
}

void VDP::setDataRegister(uint8_t value) {
    // Data register handles various VDP operations (tile map, sprite positioning, etc.)
    dataRegister = value;
    std::cout << "VDP Data Register set to: " << std::hex << (int)value << std::endl;
}

uint8_t VDP::getStatusRegister() const {
    // This is just a simple placeholder for now
    return 0x00;  // Returning 0 as the status (you can implement real status bits)
}

void VDP::renderFrame(SDL_Renderer* renderer) {
    // Render a frame by combining background and sprite rendering

    // For simplicity, we'll just emulate the process:
    emulateCycle();

    // Render background and sprites using SDL2 renderer
    renderBackground(renderer);
    renderSprites(renderer);
}

void VDP::renderBackground(SDL_Renderer* renderer) {
    // Render a basic background (in a real emulator, this
    // would be based on the tile map loaded earlier)
    std::cout << "Rendering background..." << std::endl;

    // Placeholder to indicate rendering; you can use SDL2 to render the tilemap to a texture here
    SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, screenWidth, screenHeight);
    if (texture) {
        SDL_UpdateTexture(texture, NULL, &screenBuffer[0], screenWidth * 4);  // Update texture with screen buffer
        SDL_RenderCopy(renderer, texture, NULL, NULL);  // Render texture to the screen
        SDL_DestroyTexture(texture);  // Clean up texture
    }
}

void VDP::renderSprites(SDL_Renderer* renderer) {
    // Render the sprites (this would include sprite positioning and rendering)
    std::cout << "Rendering sprites..." << std::endl;

    // For simplicity, we're just going to print some debugging output for now
    for (size_t i = 0; i < sprites.size(); ++i) {
        std::cout << "Rendering sprite " << i << " with data: " << (int)sprites[i] << std::endl;
    }
}
