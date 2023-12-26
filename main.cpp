#include <iostream>
#include "raylib.h"
#include "Characters/Fighter_Andi.h"
#include "Utils/AsepriteManager.h"
#include "Constants.h"

Rectangle CalculateScaledRectangle(RenderTexture2D target, int gameScreenWidth, int gameScreenHeight);


//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialize window
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1920;
    const int screenHeight = 1080;
    InitWindow(screenWidth, screenHeight, "C++ gbFighter");

    // Create a RenderTexture2D to be used for render to texture
    const int gameScreenWidth = 960;
    const int gameScreenHeight = 540;
    RenderTexture2D target = LoadRenderTexture(gameScreenWidth, gameScreenHeight);

    // Setup the viewport rectangle properly scaled
    Rectangle scaledRec;

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    AsepriteManager asepriteManager{"Assets/Graphics/"};
    asepriteManager.loadAnimFile("gbFighter");
    asepriteManager.showLoadedAnimFiles();



    auto* player = new BaseGameObject(200, 540-32*4);
    player->setScale(4, 4);


    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        float deltaTime = GetFrameTime();

        // Assign calculated result from function to scaledRec
        scaledRec = CalculateScaledRectangle(target, gameScreenWidth, gameScreenHeight);

        //----------------------------------------------------------------------------------
        // Update
        //----------------------------------------------------------------------------------
        player->update(deltaTime);

        //----------------------------------------------------------------------------------
        // Draw to RenderTexture
        //----------------------------------------------------------------------------------
        BeginTextureMode(target);

        ClearBackground(RAYWHITE);

        player->draw();


        DrawText("Amazing Graphics goes here :)", 190, 200, 20, LIGHTGRAY);

        EndTextureMode();


        //----------------------------------------------------------------------------------
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        //player->draw();
        //DrawText("Amazing Graphics goes here :)", 190, 200, 20, LIGHTGRAY);

        // Draw RenderTexture to Screen
        DrawTexturePro(target.texture, (Rectangle){ 0.0f, 0.0f, (float)target.texture.width, (float)-target.texture.height }, scaledRec, (Vector2){ 0, 0 }, 0.0f, WHITE);
        #ifdef DEBUG
            DrawFPS(10, 10);
        #endif

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}


// Function to calculate scaled rectangle dimensions
Rectangle CalculateScaledRectangle(RenderTexture2D target, int gameScreenWidth, int gameScreenHeight) {
    target.texture.height = GetScreenHeight();
    target.texture.width = (float)target.texture.height*((float)gameScreenWidth/(float)gameScreenHeight);
    int scaleHangover = 0;

    if (target.texture.width > GetScreenWidth())
    {
        target.texture.width = GetScreenWidth();
        target.texture.height = (float)target.texture.width*((float)gameScreenHeight/(float)gameScreenWidth);
    }

    scaleHangover = (GetScreenWidth() - (int)target.texture.width) % 2;
    target.texture.width += scaleHangover;

    return (Rectangle){ static_cast<float>((GetScreenWidth() - target.texture.width)/2), static_cast<float>((GetScreenHeight() - target.texture.height)/2), static_cast<float>(target.texture.width), static_cast<float>(target.texture.height) };
}