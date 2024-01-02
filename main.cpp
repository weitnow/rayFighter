#include <iostream>
#include "raylib.h"
#include "Characters/Fighter_Andi.h"
#include "Utils/AsepriteManager.h"
#include "Constants.h"
#include "Utils/Screen2DManager.h"
#include "GameObjects/BaseGameObject.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialize screen2DManager and set window size and title
    Screen2DManager screen2DManager(1920, 1080, "C++ gbFighter");

    // Create a RenderTexture2D to be used for render to texture
    screen2DManager.createRenderTarget("mainRenderTarget", 480, 270);


    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    AsepriteManager asepriteManager{"Assets/Graphics/"};
    asepriteManager.loadAnimFile("gbFighter");
    asepriteManager.showLoadedAnimFiles();


    auto* player1 = new BaseGameObject(200, 270 - 48);
    player1->addCollisionBox("body");



    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        float deltaTime = GetFrameTime();

        //----------------------------------------------------------------------------------
        // Update
        //----------------------------------------------------------------------------------
        player1->update(deltaTime);
        screen2DManager.update(deltaTime);

        //----------------------------------------------------------------------------------
        // Draw to RenderTexture
        //----------------------------------------------------------------------------------

        //BeginTextureMode(target);
        screen2DManager.beginDrawToRenderTarget("mainRenderTarget");

        ClearBackground(RAYWHITE);

        player1->draw();

        /*
        BeginMode2D(camera);

        player1->draw();
        player2->draw();

        EndMode2D();
        */

        DrawText("This is the Rendertarget - mainRenderTarget", 190, 200, 20, LIGHTGRAY);

        screen2DManager.endDrawToRenderTarget();


        //----------------------------------------------------------------------------------
        // Draw to Screen
        //----------------------------------------------------------------------------------
        screen2DManager.beginDrawToScreen();

        ClearBackground(RAYWHITE);

        // Draw RenderTexture to Screen
        screen2DManager.drawRenderTarget("mainRenderTarget");

        DrawText("Using [A]/[S] to change camera rotation", 10, 10+30, 20, BLACK);
        DrawText("Using [Z]/[X] to change camera zoom", 10, 40+30, 20, BLACK);

        #ifdef DEBUG
            DrawFPS(10, 10);
        #endif

        screen2DManager.endDrawToScreen();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

