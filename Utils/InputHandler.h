#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include "raylib.h"

class InputHandler
{
public:
    InputHandler();
    ~InputHandler();

    void Update();

    // Keyboard input
    bool IsKeyPressed(int key) const;
    bool IsKeyDown(int key) const;
    bool IsKeyReleased(int key) const;
    bool IsKeyUp(int key) const;

    // Gamepad input
    bool IsGamepadButtonPressed(int gamepad, int button) const;
    bool IsGamepadButtonDown(int gamepad, int button) const;
    bool IsGamepadButtonReleased(int gamepad, int button) const;
    bool IsGamepadButtonUp(int gamepad, int button) const;
};

#endif // INPUT_HANDLER_H
