#include "BaseState.h"
#include "../Utils/CollisionManager.h"
#include "Game.h"
BaseState::BaseState(Game* game) : game(game)
{

    screen2DManager = game->screen2DManager;
    soundManager = game->soundManager;
    inputHandler = game->inputHandler;
    asepriteManager = game->asepriteManager;
    debugInfo = game->debugInfo;
    gameManager = game->gameManager;
    player1 = nullptr;
    player2 = nullptr;
    collisionManager = nullptr;
}

BaseState::~BaseState()
{
}

void BaseState::Enter()
{
    // Initialization for the game scene
    if (!Global::debugMode)
    {
        //set resolution of the renderTarget to full HD
        game->screen2DManager->setResolution(Resolution::R_1920x1080);
    }
}
