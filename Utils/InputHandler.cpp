#include "InputHandler.h"


InputHandler::InputHandler()
{
}

InputHandler::~InputHandler()
{
}

void InputHandler::Update()
{
}

// Keyboard input
bool InputHandler::IsKeyPressed(int key) const
{
    return ::IsKeyPressed(key); // Use :: to refer to the global scope function
}

bool InputHandler::IsKeyDown(int key) const
{
    return ::IsKeyDown(key);
}

bool InputHandler::IsKeyReleased(int key) const
{
    return ::IsKeyReleased(key);
}

bool InputHandler::IsKeyUp(int key) const
{
    return ::IsKeyUp(key);
}

// Gamepad input
bool InputHandler::IsGamepadButtonPressed(int gamepad, int button) const
{
    return ::IsGamepadButtonPressed(gamepad, button);
}

bool InputHandler::IsGamepadButtonDown(int gamepad, int button) const
{
    return ::IsGamepadButtonDown(gamepad, button);
}

bool InputHandler::IsGamepadButtonReleased(int gamepad, int button) const
{
    return ::IsGamepadButtonReleased(gamepad, button);
}

bool InputHandler::IsGamepadButtonUp(int gamepad, int button) const
{
    return ::IsGamepadButtonUp(gamepad, button);
}
