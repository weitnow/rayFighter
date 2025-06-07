#include "Game/CharSelectState.h"
#include "Game/Game.h"

#include "Game/IntroState.h"



//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------

    // main.cpp
int main(void)
{
    auto game = std::make_unique<Game>();
    game->init();

    game->ChangeState(std::make_unique<IntroState>(game.get()));

    // Main game loop
    while (!game->quit)
    {
        game->Update();
        game->Render();
    }

    CloseWindow(); // Close window and OpenGL context

    return 0;
}