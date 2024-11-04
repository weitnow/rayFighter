#include "InputHandler.h"


InputHandler::InputHandler()
{
    player1Controller = new CharacterController();
    player2Controller = new CharacterController();
}

InputHandler::~InputHandler()
{
    delete player1Controller;
    delete player2Controller;
}

void InputHandler::Update()
{
    // player 1
    _resetBoolsToFalse(player1Controller);
    _handlePlayer1Input();


    // player 2
    _resetBoolsToFalse(player2Controller);
    _handlePlayer2Input();

    // game controls
    _handleGameInput();
}


void InputHandler::addDebugInfo(DebugInfo& debugInfo)
{
    this->debugInfo = &debugInfo;
}

CharacterController* const InputHandler::getPlayer2Controller()
{
    return player2Controller;
}

CharacterController* const InputHandler::getPlayer1Controller()
{
    return player1Controller;
}

void InputHandler::_resetBoolsToFalse(CharacterController* controller)
{
    controller->moveLeft = false;
    controller->moveRight = false;
    controller->jump = false;
    controller->duck = false;
    controller->punch = false;
    controller->kick = false;
    controller->block = false;
}

void InputHandler::_handlePlayer1Input()
{
    if (IsKeyDown(KEY_A))
    {
        //gameManager->getBaseCharacter("player1")->moveLeft();
        player1Controller->moveLeft = true;
    }
    else if (IsKeyDown(KEY_D))
    {
        //gameManager->getBaseCharacter("player1")->moveRight();
        player1Controller->moveRight = true;
    }

    if (IsKeyDown(KEY_W))
    {
        //gameManager->getBaseCharacter("player1")->jump();
        player1Controller->jump = true;
    }
    else if (IsKeyDown(KEY_S))
    {
        //gameManager->getBaseCharacter("player1")->duck();
        player1Controller->duck = true;
    }

    if (IsKeyPressed(KEY_J))
    {
        //gameManager->getBaseCharacter("player1")->punch();
        player1Controller->punch = true;
    }
    if (IsKeyPressed(KEY_K))
    {
        //gameManager->getBaseCharacter("player1")->kick();
        player1Controller->kick = true;
    }
    if (IsKeyDown(KEY_L))
    {
        //gameManager->getBaseCharacter("player1")->block();
        player1Controller->block = true;
    }
}

void InputHandler::_handlePlayer2Input()
{
    if (IsKeyDown(KEY_LEFT))
    {
        //gameManager->getBaseCharacter("player2")->moveLeft();
        player2Controller->moveLeft = true;
    }
    else if (IsKeyDown(KEY_RIGHT))
    {
        //gameManager->getBaseCharacter("player2")->moveRight();
        player2Controller->moveRight = true;
    }

    if (IsKeyDown(KEY_UP))
    {
        //gameManager->getBaseCharacter("player2")->jump();
        player2Controller->jump = true;
    }
    else if (IsKeyDown(KEY_DOWN))
    {
        //gameManager->getBaseCharacter("player2")->duck();
        player2Controller->duck = true;
    }

    if (IsKeyPressed(KEY_U))
    {
        //gameManager->getBaseCharacter("player2")->punch();
        player2Controller->punch = true;
    }
    if (IsKeyPressed(KEY_I))
    {
        //gameManager->getBaseCharacter("player2")->kick();
        // not implemented yet
    }
    if (IsKeyDown(KEY_O))
    {
        //gameManager->getBaseCharacter("player2")->block();
        player2Controller->block = true;
    }
}

void InputHandler::_handleGameInput()
{
    // DebugInput
    if (IsKeyPressed(KEY_SPACE))
    {
        debugInfo->showNextGameObject();
    }

    if (IsKeyPressed(KEY_Q))
    {
        Global::debugMode = !Global::debugMode;

        // Todo: replace this with another method
        //gameManager->setDebugMode(Global::debugMode);
    }
}
