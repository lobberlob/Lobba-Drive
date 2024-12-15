#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "CPU.h"
#include "VDP.h"
#include "Audio.h"
#include "InputHandler.h"

class LobbaDrive {
public:
    bool initialize() {
        // Initialize SDL2 for video, audio, and joystick input
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK | SDL_INIT_EVENTS) != 0) {
            std::cerr << "SDL Initialization failed: " << SDL_GetError() << std::endl;
            return false;
        }

        // Initialize SDL2_image for loading textures
        if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == 0) {
            std::cerr << "SDL2_image Initialization failed: " << SDL_GetError() << std::endl;
            return false;
        }

        // Initialize the window and renderer using SDL2 (no OpenGL)
        window = SDL_CreateWindow("Lobba Emulator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            screenWidth, screenHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);
        if (!window) {
            std::cerr << "Window creation failed: " << SDL_GetError() << std::endl;
            return false;
        }

        // Create an SDL2 renderer (no need for OpenGL)
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (!renderer) {
            std::cerr << "Renderer creation failed: " << SDL_GetError() << std::endl;
            return false;
        }

        // Initialize the CPU, VDP (graphics), and audio components
        cpu.initialize();
        vdp.initialize();
        audio.initialize();

        // Setup controller input
        inputHandler.initialize();

        // Enable drag and drop
        SDL_SetEventFilter(&LobbaDrive::eventFilter, this);

        return true;
    }

    void loadROM(const std::string& romPath) {
        cpu.loadROM(romPath);  // Load ROM into memory
    }

    void run() {
        while (isRunning) {
            // Handle user input (keyboard, joystick, etc.)
            handleInput();

            // Emulate one cycle of the CPU
            cpu.emulateCycle();

            // Render the frame using VDP (Video Display Processor)
            vdp.renderFrame(renderer);  // Pass the renderer to VDP for rendering

            // Update audio output
            audio.update();

            // Present the rendered frame using SDL_RenderPresent (not OpenGL)
            SDL_RenderPresent(renderer);
        }
    }

    void handleInput() {
        // Update controller state and process input
        inputHandler.update();
    }

    // Event filter to capture drag-and-drop events
    static int eventFilter(void* userdata, SDL_Event* event) {
        if (event->type == SDL_DROPFILE) {
            // Handle the dropped file
            char* filePath = event->drop.file;
            std::cout << "File dropped: " << filePath << std::endl;

            // Load the ROM from the dropped file path
            LobbaDrive* emulator = static_cast<LobbaDrive*>(userdata);
            emulator->loadROM(filePath);

            // Free the file path memory allocated by SDL!!
            SDL_free(filePath);
        }
        return 1;
    }

private:
    SDL_Window* window;           
    SDL_Renderer* renderer;       
    CPU cpu;                     
    VDP vdp;                      
    Audio audio;                  
    InputHandler inputHandler;    
    bool isRunning = true;        

    const int screenWidth = 320;  
    const int screenHeight = 224; 
};

int main(int argc, char* argv[]) {
    // Create the emulator object
    LobbaDrive emulator;

    // Initialize the emulator system (SDL, CPU, etc.)
    if (!emulator.initialize()) {
        return -1;  // Initialization failed
    }

    // Run the emulator loop (emulating CPU cycles, rendering, etc.)
    emulator.run();

    
    SDL_Quit();
    IMG_Quit();  

    return 0;
}
/*fuck you sdl*/
