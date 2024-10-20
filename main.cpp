#include "Characters/Fighter1.h"
#include "Characters/Fighter2.h"
#include "Constants.h"
#include "Game/Game.h"
#include "Game/GameState.h"
#include "Game/MenuState.h"
#include "GameObjects/BaseGameObject.h"
#include "GameObjects/Items/Barrel.h"
#include "Utils/AsepriteManager.h"
#include "Utils/CollisionManager.h"
#include "Utils/Core.h"
#include "Utils/DebugInfo.h"
#include "Utils/GameManager.h"
#include "Utils/HelperFunctions.h"
#include "Utils/InputHandler.h"
#include "Utils/Screen2DManager.h"
#include "Utils/SoundManager.h"
#include "raylib.h"
#include <iostream>

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    Game* game = new Game(); // will initialize all global components

    game->ChangeState(std::make_unique<GameState>(game));


    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        game->Update();
        game->Render();

        // if key is presssd //Todo: refactor this to inputHandler
        if (IsKeyPressed(KEY_Q))
        {
            Global::debugMode = !Global::debugMode;
            game->gameManager->setDebugMode(Global::debugMode);
        }
    }


    //----------------------------------------------------------------------------------
    // De-Initialization
    //--------------------------------------------------------------------------------------
    delete game;

    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
