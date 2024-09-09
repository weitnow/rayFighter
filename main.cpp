#include "Characters/BaseCharacter.h"
#include "Characters/Fighter_Andi.h"
#include "Constants.h"
#include "GameObjects/BaseGameObject.h"
#include "Utils/AsepriteManager.h"
#include "Utils/DebugInfo.h"
#include "Utils/GameObjectsManager.h"
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

    if (IsKeyDown(KEY_W))
    {
        player1->jump();
    }
    else if (IsKeyDown(KEY_S))
    {
        player1->duck();
    }
}

void handleInput(DebugInfo* debugInfo)
{
    if (IsKeyPressed(KEY_SPACE))
    {
        debugInfo->showNextGameObject();
    }
}

void handleInput(GameObjectsManager& gameObjectsManager, BaseCharacter* player1, BaseCharacter* player2)
{
    if (IsKeyPressed(KEY_ONE))
    {
        gameObjectsManager.removeBaseCharacter("player1");
    }
    if (IsKeyPressed(KEY_TWO))
    {
        gameObjectsManager.removeBaseCharacter("player3");
    }
}


//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{

    // Initialize screen2DManager and set window size and title, this has to be done first before everything else
    Screen2DManager* screen2DManager =
        new Screen2DManager(Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT, "C++ gbFighter");

    // Initialize InputHandler
    InputHandler* inputHandler = new InputHandler();

    // Initialize global Variables and GlobalObjects
    float deltaTime;                                                            // will be updated in the main game loop
    AsepriteManager* asepriteManager = new AsepriteManager{"Assets/Graphics/"}; // instance of AsepriteManager
    DebugInfo* debugInfo = new DebugInfo();                                     // instance of DebugInfo
    GameObjectsManager& gameObjectsManager = GameObjectsManager::getInstance(); // instance of GameObjectsManager

    SetTargetFPS(60); // Set  game to run at 60 frames-per-second

    // Populate membervariables of the GlobalObjects
    screen2DManager->createRenderTarget(
        "mainRenderTarget",
        Constants::RENDERTARGET_WIDTH,
        Constants::RENDERTARGET_HEIGHT); // Create a RenderTexture2D to be used for render to texture


    asepriteManager->loadAnimFile("gbFighter"); // asepriteManager.frameTags[gbFighter-Idle]
                                                // asepriteManager.textures[gbFighter]


    asepriteManager->loadAnimFile("nesFighter"); // asepriteManager.frameTags[nesFighter-Idle]
                                                 // asepriteManager.textures[nesFighter]

    asepriteManager->loadAnimFile("bgAnimation"); // asepriteManager.frameTags[bgAnimation]
                                                  // asepriteManager.textures[bgAnimation]

    // Create Player 1
    BaseCharacter* player1 = new BaseCharacter(asepriteManager, Constants::PLAYER1_X, Constants::BASELINE);
    player1->setCurrentFrameTag("gbFighter-Idle");

    // Create Player 2
    BaseCharacter* player2 = new BaseCharacter(asepriteManager, Constants::PLAYER2_X, Constants::BASELINE);
    player2->setCurrentFrameTag("nesFighter-Idle");

    gameObjectsManager.addBaseCharacter("player1", player1);
    gameObjectsManager.addBaseCharacter("player2", player2);

    // Create Static Background
    Texture2D stage = LoadTexture("Assets/Graphics/stage.png");


#ifdef DEBUG
    debugInfo->addGameObject("Player1", player1);
    debugInfo->addGameObject("Player2", player2);
#endif


    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        deltaTime = GetFrameTime(); // update global Variable deltaTime

        //----------------------------------------------------------------------------------
        // Update
        //----------------------------------------------------------------------------------


        // check keyboard input
        // todo: replace with inputHandler and remove handleInput function

        handleInput(debugInfo);
        handleInput(gameObjectsManager, player1, player2);

        screen2DManager->update(deltaTime);

        gameObjectsManager.update(deltaTime);
        //player1->update(deltaTime);
        handleInput(player1);
        //player2->update(deltaTime);


        //----------------------------------------------------------------------------------
        // Draw to RenderTexture
        //----------------------------------------------------------------------------------

        // BeginTextureMode(target);
        screen2DManager->beginDrawToRenderTarget("mainRenderTarget");

        ClearBackground(RAYWHITE);

        // draw stage
        float stage_scale = 1.f;
        DrawTextureEx(stage, {0, 80}, 0, stage_scale, WHITE);

        //player1->draw();
        //player2->draw();
        gameObjectsManager.draw();

        /*
        BeginMode2D(camera);

        player1->draw();
        player2->draw();

        EndMode2D();
        */


        screen2DManager->endDrawToRenderTarget();

        //----------------------------------------------------------------------------------
        // Draw to Screen
        //----------------------------------------------------------------------------------
        screen2DManager->beginDrawToScreen();

        // Draw RenderTexture to Screen
        screen2DManager->drawRenderTarget("mainRenderTarget");

#ifdef DEBUG
        debugInfo->draw();
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
    delete debugInfo;       //deallocate memory on the heap

    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------


    return 0;
}
