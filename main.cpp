#include <iostream>
#include "raylib.h"
#include "Characters/Fighter_Andi.h"
#include "Utils/AsepriteManager.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;


    InitWindow(screenWidth, screenHeight, "C++ gbFighter");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    AsepriteManager asepriteManager{"Assets/Graphics/"};
    asepriteManager.loadAnimFile("gbFighter");
    asepriteManager.showLoadedAnimFiles();




    //auto* player = new Fighter_Andi(100, 300);
    auto* player = new BaseGameObject();
    player->setScale(1, 1);

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        player->update();
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        player->draw();
        DrawText("Amazing Graphics goes here :)", 190, 200, 20, LIGHTGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
