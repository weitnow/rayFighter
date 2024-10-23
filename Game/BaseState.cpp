#include "BaseState.h"
#include "Game.h"

void BaseState::Enter()
{
    // Initialization for the game scene
    if (!Global::debugMode)
    {
        //set resolution of the renderTarget to full HD
        game->screen2DManager->setResolution(Resolution::R_1920x1080);
    }
}
