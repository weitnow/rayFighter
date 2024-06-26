#include "Characters/Fighter_Andi.h"
#include "Constants.h"
#include "GameObjects/BaseGameObject.h"
#include "Utils/AsepriteManager.h"
#include "Utils/Screen2DManager.h"
#include "raylib.h"
#include <iostream>

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialize screen2DManager and set window size and title, this has to be done first before everything else
    Screen2DManager* screen2DManager = new Screen2DManager(1920, 1080, "C++ gbFighter");

    // Initialize global Variables and GlobalObjects
    float deltaTime;                                                            // will be updated in the main game loop
    AsepriteManager* asepriteManager = new AsepriteManager{"Assets/Graphics/"}; // instance of AsepriteManager
    SetTargetFPS(60); // Set  game to run at 60 frames-per-second

    // Populate membervariables of the GlobalObjects
    screen2DManager->createRenderTarget("mainRenderTarget",
                                        480,
                                        270); // Create a RenderTexture2D to be used for render to texture


    asepriteManager->loadAnimFile("gbFighter"); // asepriteManager.frameTags[gbFighter-Idle]
                                                // asepriteManager.textures[gbFighter]

    // Create Player 1
    BaseGameObject* player1 = new BaseGameObject(80, 270 - 48);
    player1->addAnim(asepriteManager->getAnimFile("gbFighter"));
    player1->getAnim()->setFrameTag("Walking");


    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        deltaTime = GetFrameTime(); // update global Variable deltaTime

        //----------------------------------------------------------------------------------
        // Update
        //----------------------------------------------------------------------------------

        screen2DManager->update(deltaTime);
        player1->update(deltaTime);
        player1->getAnim()->update(deltaTime);


        //----------------------------------------------------------------------------------
        // Draw to RenderTexture
        //----------------------------------------------------------------------------------

        // BeginTextureMode(target);
        screen2DManager->beginDrawToRenderTarget("mainRenderTarget");

        ClearBackground(RAYWHITE);

        player1->draw();
        player1->getAnim()->drawCurrentSelectedTag(player1->getPos().x, player1->getPos().y);

        /*
        BeginMode2D(camera);

        player1->draw();
        player2->draw();

        EndMode2D();
        */

        DrawText("This is the Rendertarget - mainRenderTarget", 190, 200, 20, LIGHTGRAY);

        screen2DManager->endDrawToRenderTarget();

        //----------------------------------------------------------------------------------
        // Draw to Screen
        //----------------------------------------------------------------------------------
        screen2DManager->beginDrawToScreen();

        // Draw RenderTexture to Screen
        screen2DManager->drawRenderTarget("mainRenderTarget");

#ifdef DEBUG
        DrawFPS(10, 10);
#endif

        screen2DManager->endDrawToScreen();
    }

    //----------------------------------------------------------------------------------
    // De-Initialization
    //--------------------------------------------------------------------------------------

    screen2DManager->unloadAllRenderTextures();
    asepriteManager->UnloadRessources();

    delete screen2DManager; //deallocate memory on the heap
    delete asepriteManager; //deallocate memory on the heap

    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------


    return 0;
}
