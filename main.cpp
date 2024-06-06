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
    // Initialize screen2DManager and set window size and title, this has to be done first before everything else
    Screen2DManager screen2DManager(1920, 1080, "C++ gbFighter");

    // Initialize global Variables and GlobalObjects
    float deltaTime;                                     // will be updated in the main game loop
    AsepriteManager asepriteManager{"Assets/Graphics/"}; // instance of AsepriteManager
    SetTargetFPS(60);                                    // Set  game to run at 60 frames-per-second

    // Populate membervariables of the GlobalObjects
    screen2DManager.createRenderTarget("mainRenderTarget", 480, 270); // Create a RenderTexture2D to be used for render to texture
    asepriteManager.loadAnimFile("gbFighter");

    // Create Player 1
    BaseGameObject *player1 = new BaseGameObject(50, 270 - 48);
    player1->addAnim(asepriteManager.getAnimFile("gbFighter"));
    player1->getAnim()->setFrameTag("Walking");
    player1->addCollisionBox("body");

    // Create Player 2
    BaseGameObject *player2 = new BaseGameObject(150, 270 - 48);
    player2->addAnim(asepriteManager.getAnimFile("gbFighter"));
    player2->getAnim()->setFrameTag("Idle");

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        deltaTime = GetFrameTime(); // update global Variable deltaTime

        //----------------------------------------------------------------------------------
        // Update
        //----------------------------------------------------------------------------------
        player1->update(deltaTime);
        screen2DManager.update(deltaTime);
        player1->getAnim()->update(deltaTime);

        //----------------------------------------------------------------------------------
        // Draw to RenderTexture
        //----------------------------------------------------------------------------------

        // BeginTextureMode(target);
        screen2DManager.beginDrawToRenderTarget("mainRenderTarget");

        ClearBackground(RAYWHITE);

        player1->draw();

        player1->getAnim()->drawCurrentSelectedTag(player1->getPos().x, player1->getPos().y);

        player2->draw();

        player2->getAnim()->drawCurrentSelectedTag(player2->getPos().x, player2->getPos().y);
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

        // Draw RenderTexture to Screen
        screen2DManager.drawRenderTarget("mainRenderTarget");

#ifdef DEBUG
        DrawFPS(10, 10);
#endif

        screen2DManager.endDrawToScreen();
    }

    //----------------------------------------------------------------------------------
    // De-Initialization
    //--------------------------------------------------------------------------------------

    screen2DManager.unloadAllRenderTextures();
    asepriteManager.UnloadRessources();

    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
