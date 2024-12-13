#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include "DebugInfo.h"
#include "raylib.h"

struct CharacterController
{
    bool moveLeft = false;
    bool moveRight = false;
    bool jump = false;
    bool duck = false;
    bool punch = false;
    bool kick = false;
    bool block = false;
};


class InputHandler
{
public:
    InputHandler();
    ~InputHandler();

    // Delete copy constructor and copy assignment
    InputHandler(const InputHandler&) = delete;
    InputHandler& operator=(const InputHandler&) = delete;

    void Update();

    void addDebugInfo(DebugInfo& debugInfo);

    CharacterController* const getPlayer1Controller();
    CharacterController* const getPlayer2Controller();

private:
    void _resetBoolsToFalse(CharacterController* controller);
    void _handlePlayer1Input();
    void _handlePlayer2Input();
    void _handleGameInput();

    CharacterController* player1Controller;
    CharacterController* player2Controller;
    DebugInfo* debugInfo;
};

#endif // INPUT_HANDLER_H
