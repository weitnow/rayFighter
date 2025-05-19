#include "Game/CharSelectState.h"
#include "Game/Game.h"
#include "Game/GameState.h"
#include "Game/IntroState.h"
#include "Game/MenuState.h"
#include "Game/OptionState.h"
#include "Game/StageSelectState.h"


//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    Game* game = new Game(); // will initialize all global components
    game->init();

    //game->ChangeState(std::make_unique<IntroState>(game));
    //game->ChangeState(std::make_unique<MenuState>(game));

    //game->ChangeState(std::make_unique<OptionSelectState>(game));

    //game->ChangeState(std::make_unique<CharSelectState>(game));
    //game->ChangeState(std::make_unique<StageSelectState>(game));
    game->ChangeState(std::make_unique<GameState>(game));


    // Main game loop
    while (!game->quit)
    {
        game->Update();
        game->Render();
    }
    //----------------------------------------------------------------------------------
    // De-Initialization
    //--------------------------------------------------------------------------------------
    delete game;

    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
