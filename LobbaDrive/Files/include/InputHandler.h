#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <SDL2/SDL.h>
#include <array>
#include <unordered_map>

class InputHandler {
public:
    InputHandler();
    ~InputHandler();

    bool initialize();
    void update();

    bool isButtonPressed(int button);
    bool isButtonReleased(int button);

    // D-pad functions
    bool isDPadUp();
    bool isDPadDown();
    bool isDPadLeft();
    bool isDPadRight();

    // Change button mappings at runtime
    void mapButtonToController(int button, SDL_GameControllerButton controllerButton);
    void mapButtonToKeyboard(int button, SDL_Scancode key);
    void resetMappings();  // Reset mappings to default

private:
    SDL_GameController* gameController;
    const Uint8* keyboardState;

    static const int BUTTON_A = 0;
    static const int BUTTON_B = 1;
    static const int BUTTON_C = 2;
    static const int BUTTON_START = 3;

    static const int DPAD_UP = 4;
    static const int DPAD_DOWN = 5;
    static const int DPAD_LEFT = 6;
    static const int DPAD_RIGHT = 7;

    std::array<bool, 8> buttonStates;
    std::unordered_map<int, SDL_GameControllerButton> controllerButtonMappings;
    std::unordered_map<int, SDL_Scancode> keyboardButtonMappings;

    // Default mappings (keyboard and controller)
    void setDefaultMappings();
};

#endif // INPUTHANDLER_H
