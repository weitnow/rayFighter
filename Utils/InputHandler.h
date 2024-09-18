#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include "DebugInfo.h"
#include "GameManager.h"
#include "raylib.h"

class InputHandler
{
public:
    InputHandler();
    ~InputHandler();

    void Update();

    void addGameManager(GameManager& gameManager);
    void addDebugInfo(DebugInfo& debugInfo);

private:
    void _handlePlayer1Input();
    void _handlePlayer2Input();
    GameManager* gameManager;
    DebugInfo* debugInfo;
};

#endif // INPUT_HANDLER_H
