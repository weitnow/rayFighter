#include "Game/CharSelectState.h"
#include "Game/Game.h"
#include "Game/GameState.h"
#include "Game/MenuState.h"


//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    Game* game = new Game(); // will initialize all global components

    //game->ChangeState(std::make_unique<GameState>(game));
    //game->ChangeState(std::make_unique<MenuState>(game));
    game->ChangeState(std::make_unique<CharSelectState>(game));


    // Main game loop
    while (!WindowShouldClose() && !game->quit) // Detect window close button or ESC key
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
