#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include "CharacterController.h"
#include "DebugInfo.h"
#include "InputBuffer.h"
#include "InputTypes.h"
#include "raylib.h"
#include <deque>


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

    InputDirection mapDirectionInput();
    InputAction mapActionInput();
    void updateInputBuffer(InputBuffer& buffer);
    void checkSpecialMoves(InputBuffer& buffer);

    CharacterController* player1Controller;
    CharacterController* player2Controller;
    DebugInfo* debugInfo;

    InputBuffer inputBuffer;
};

#endif // INPUT_HANDLER_H
