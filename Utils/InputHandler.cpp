#include "InputHandler.h"


InputHandler::InputHandler()
{
}

InputHandler::~InputHandler()
{
}

void InputHandler::Update()
{
    /* #region Player 1 and 2 Input */

    // check if player 1 exists
    if (gameManager->getBaseCharacter("player1") != nullptr)
        _handlePlayer1Input();

    // check if player 2 exists
    if (gameManager->getBaseCharacter("player2") != nullptr)
        _handlePlayer2Input();

    /* #endregion */

    /* #region Debug Input */
    if (IsKeyPressed(KEY_SPACE))
    {
        debugInfo->showNextGameObject();
    }
    /* #endregion */

    /* #region Game Input */
    if (IsKeyPressed(KEY_ONE))
    {
        gameManager->removeBaseCharacter("player1");
    }
    if (IsKeyPressed(KEY_TWO))
    {
        gameManager->removeBaseCharacter("player2");
    }
    /* #endregion */
}


void InputHandler::addGameManager(GameManager& gameManager)
{
    this->gameManager = &gameManager;
}

void InputHandler::addDebugInfo(DebugInfo& debugInfo)
{
    this->debugInfo = &debugInfo;
}

void InputHandler::_handlePlayer1Input()
{
    if (IsKeyDown(KEY_A))
    {
        gameManager->getBaseCharacter("player1")->moveLeft();
    }
    else if (IsKeyDown(KEY_D))
    {
        gameManager->getBaseCharacter("player1")->moveRight();
    }
    else
    {
        gameManager->getBaseCharacter("player1")->stop();
    }

    if (IsKeyDown(KEY_W))
    {
        gameManager->getBaseCharacter("player1")->jump();
    }
    else if (IsKeyDown(KEY_S))
    {
        gameManager->getBaseCharacter("player1")->duck();
    }

    if (IsKeyPressed(KEY_J))
    {
        gameManager->getBaseCharacter("player1")->punch();
    }
}

void InputHandler::_handlePlayer2Input()
{
    if (IsKeyDown(KEY_LEFT))
    {
        gameManager->getBaseCharacter("player2")->moveLeft();
    }
    else if (IsKeyDown(KEY_RIGHT))
    {
        gameManager->getBaseCharacter("player2")->moveRight();
    }
    else
    {
        gameManager->getBaseCharacter("player2")->stop();
    }
}
