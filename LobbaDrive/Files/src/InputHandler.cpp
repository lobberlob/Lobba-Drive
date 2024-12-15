#include "InputHandler.h"
#include <iostream>

InputHandler::InputHandler() : gameController(nullptr), keyboardState(nullptr) {
    buttonStates.fill(false);
    setDefaultMappings();
}

InputHandler::~InputHandler() {
    if (gameController) {
        SDL_GameControllerClose(gameController);
    }
    SDL_QuitSubSystem(SDL_INIT_GAMECONTROLLER);
}

bool InputHandler::initialize() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER | SDL_INIT_EVENTS) < 0) {
        std::cerr << "SDL initialization failed: " << SDL_GetError() << std::endl;
        return false;
    }

    if (SDL_NumJoysticks() > 0) {
        gameController = SDL_GameControllerOpen(0);
        if (!gameController) {
            std::cerr << "Could not open game controller: " << SDL_GetError() << std::endl;
            return false;
        }
    }
    else {
        std::cerr << "No game controllers found!" << std::endl;
        return false;
    }

    keyboardState = SDL_GetKeyboardState(NULL);
    return true;
}

void InputHandler::update() {
    SDL_GameControllerUpdate();

    // Update button states based on controller mappings
    buttonStates[BUTTON_A] = SDL_GameControllerGetButton(gameController, controllerButtonMappings[BUTTON_A]);
    buttonStates[BUTTON_B] = SDL_GameControllerGetButton(gameController, controllerButtonMappings[BUTTON_B]);
    buttonStates[BUTTON_C] = SDL_GameControllerGetButton(gameController, controllerButtonMappings[BUTTON_C]);
    buttonStates[BUTTON_START] = SDL_GameControllerGetButton(gameController, controllerButtonMappings[BUTTON_START]);

    buttonStates[DPAD_UP] = SDL_GameControllerGetAxis(gameController, SDL_CONTROLLER_AXIS_LEFTY) < -3200;
    buttonStates[DPAD_DOWN] = SDL_GameControllerGetAxis(gameController, SDL_CONTROLLER_AXIS_LEFTY) > 3200;
    buttonStates[DPAD_LEFT] = SDL_GameControllerGetAxis(gameController, SDL_CONTROLLER_AXIS_LEFTX) < -3200;
    buttonStates[DPAD_RIGHT] = SDL_GameControllerGetAxis(gameController, SDL_CONTROLLER_AXIS_LEFTX) > 3200;

    // Keyboard input processing
    buttonStates[BUTTON_A] |= keyboardState[keyboardButtonMappings[BUTTON_A]];
    buttonStates[BUTTON_B] |= keyboardState[keyboardButtonMappings[BUTTON_B]];
    buttonStates[BUTTON_C] |= keyboardState[keyboardButtonMappings[BUTTON_C]];
    buttonStates[BUTTON_START] |= keyboardState[keyboardButtonMappings[BUTTON_START]];

    buttonStates[DPAD_UP] |= keyboardState[keyboardButtonMappings[DPAD_UP]];
    buttonStates[DPAD_DOWN] |= keyboardState[keyboardButtonMappings[DPAD_DOWN]];
    buttonStates[DPAD_LEFT] |= keyboardState[keyboardButtonMappings[DPAD_LEFT]];
    buttonStates[DPAD_RIGHT] |= keyboardState[keyboardButtonMappings[DPAD_RIGHT]];
}

bool InputHandler::isButtonPressed(int button) {
    if (button < 0 || button >= buttonStates.size()) {
        std::cerr << "Invalid button index!" << std::endl;
        return false;
    }
    return buttonStates[button];
}

bool InputHandler::isButtonReleased(int button) {
    return !isButtonPressed(button);
}

bool InputHandler::isDPadUp() {
    return isButtonPressed(DPAD_UP);
}

bool InputHandler::isDPadDown() {
    return isButtonPressed(DPAD_DOWN);
}

bool InputHandler::isDPadLeft() {
    return isButtonPressed(DPAD_LEFT);
}

bool InputHandler::isDPadRight() {
    return isButtonPressed(DPAD_RIGHT);
}

// Map controller button to a custom button
void InputHandler::mapButtonToController(int button, SDL_GameControllerButton controllerButton) {
    if (button >= 0 && button < 8) {
        controllerButtonMappings[button] = controllerButton;
    }
}

// Map keyboard key to a custom button
void InputHandler::mapButtonToKeyboard(int button, SDL_Scancode key) {
    if (button >= 0 && button < 8) {
        keyboardButtonMappings[button] = key;
    }
}

// Reset mappings to default
void InputHandler::resetMappings() {
    setDefaultMappings();
}

void InputHandler::setDefaultMappings() {
    // Set default controller mappings
    controllerButtonMappings[BUTTON_A] = SDL_CONTROLLER_BUTTON_A;
    controllerButtonMappings[BUTTON_B] = SDL_CONTROLLER_BUTTON_B;
    controllerButtonMappings[BUTTON_C] = SDL_CONTROLLER_BUTTON_X;
    controllerButtonMappings[BUTTON_START] = SDL_CONTROLLER_BUTTON_START;

    // Set default keyboard mappings
    keyboardButtonMappings[BUTTON_A] = SDL_SCANCODE_Z;
    keyboardButtonMappings[BUTTON_B] = SDL_SCANCODE_X;
    keyboardButtonMappings[BUTTON_C] = SDL_SCANCODE_C;
    keyboardButtonMappings[BUTTON_START] = SDL_SCANCODE_RETURN;

    keyboardButtonMappings[DPAD_UP] = SDL_SCANCODE_W;
    keyboardButtonMappings[DPAD_DOWN] = SDL_SCANCODE_S;
    keyboardButtonMappings[DPAD_LEFT] = SDL_SCANCODE_A;
    keyboardButtonMappings[DPAD_RIGHT] = SDL_SCANCODE_D;
}
