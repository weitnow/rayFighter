#include <iostream>
#include "raylib.h"
#include "Characters/BaseCharacter.h"
#include "Utils/Aseprite.h"
#include <assert.h>

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
    asepriteManager.loadAnimation("gbFighter");
    auto aseprite_ptr = asepriteManager.asepriteObjs["gbFighter"];

    for(const auto &pair : aseprite_ptr->frameTags) {
        std::cout << pair.first << std::endl;
        std::cout << pair.second.first << std::endl;
        std::cout << pair.second.second << std::endl;
    }

    auto* player = new BaseCharacter(100, 100);



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
