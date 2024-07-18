#include "Characters/BaseCharacter.h"
#include "Characters/Fighter_Andi.h"
#include "Constants.h"
#include "GameObjects/BaseGameObject.h"
#include "Utils/AsepriteManager.h"
#include "Utils/InputHandler.h"
#include "Utils/Screen2DManager.h"
#include "raylib.h"
#include <iostream>


//------------------------------------------------------------------------------------
// Temporary function to handle input, will be replaced by InputHandler later
//------------------------------------------------------------------------------------
void handleInput(BaseCharacter* player1)
{
    if (IsKeyDown(KEY_A))
    {
        player1->moveLeft();
    }
    else if (IsKeyDown(KEY_D))
    {
        player1->moveRight();
    }
    else
    {
        player1->stop();
    }

    if (IsKeyPressed(KEY_W))
    {
        player1->jump();
    }
    else if (IsKeyPressed(KEY_S))
    {
        player1->duck();
    }
}

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialize screen2DManager and set window size and title, this has to be done first before everything else
    Screen2DManager* screen2DManager = new Screen2DManager(1920, 1080, "C++ gbFighter");

    // Initialize InputHandler
    InputHandler* inputHandler = new InputHandler();

    // Initialize global Variables and GlobalObjects
    float deltaTime;                                                            // will be updated in the main game loop
    AsepriteManager* asepriteManager = new AsepriteManager{"Assets/Graphics/"}; // instance of AsepriteManager
    SetTargetFPS(60); // Set  game to run at 60 frames-per-second

    // Populate membervariables of the GlobalObjects
    screen2DManager->createRenderTarget("mainRenderTarget",
                                        320,
                                        180); // Create a RenderTexture2D to be used for render to texture


    asepriteManager->loadAnimFile("gbFighter"); // asepriteManager.frameTags[gbFighter-Idle]
                                                // asepriteManager.textures[gbFighter]


    asepriteManager->loadAnimFile("nesFighter"); // asepriteManager.frameTags[nesFighter-Idle]
                                                 // asepriteManager.textures[nesFighter]

    asepriteManager->loadAnimFile("bgAnimation"); // asepriteManager.frameTags[bgAnimation]
                                                  // asepriteManager.textures[bgAnimation]

    // Create Player 1
    BaseCharacter* player1 = new BaseCharacter(80, 190 - 48);
    player1->addAnim(asepriteManager->getAnimFile("gbFighter"));
    player1->getAnim()->setFrameTag("gbFighter-Idle");

    // Create Player 2
    BaseGameObject* player2 = new BaseGameObject(120, 190 - 48);
    player2->addAnim(asepriteManager->getAnimFile("nesFighter"));
    player2->getAnim()->setFrameTag("nesFighter-Idle");

    // Create Animated-Background
    BaseGameObject* bg = new BaseGameObject(120, 0);
    bg->addAnim(asepriteManager->getAnimFile("bgAnimation"));
    bg->getAnim()->setFrameTag("bgAnimation");

    // Create Static Background
    Texture2D stage = LoadTexture("Assets/Graphics/stage.png");


    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        deltaTime = GetFrameTime(); // update global Variable deltaTime

        //----------------------------------------------------------------------------------
        // Update
        //----------------------------------------------------------------------------------


        // check keyboard input
        // todo: replace with inputHandler and remove handleInput function
        handleInput(player1);

        screen2DManager->update(deltaTime);

        player1->update(deltaTime);
        player2->update(deltaTime);
        bg->update(deltaTime);


        //----------------------------------------------------------------------------------
        // Draw to RenderTexture
        //----------------------------------------------------------------------------------

        // BeginTextureMode(target);
        screen2DManager->beginDrawToRenderTarget("mainRenderTarget");

        ClearBackground(RAYWHITE);

        // draw stage
        float stage_scale = 1.f;
        DrawTextureEx(stage, {0, 80}, 0, stage_scale, WHITE);

        player1->draw();
        player2->draw();
        bg->draw();


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

    delete player1;
    delete player2;

    screen2DManager->unloadAllRenderTextures();
    UnloadTexture(stage);
    delete screen2DManager; //deallocate memory on the heap
    delete inputHandler;    //deallocate memory on the heap
    delete asepriteManager; //deallocate memory on the heap

    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------


    return 0;
}
