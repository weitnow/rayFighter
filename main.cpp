#include "Characters/BaseCharacter.h"
#include "Characters/Fighter_Andi.h"
#include "Constants.h"
#include "GameObjects/BaseGameObject.h"
#include "Utils/AsepriteManager.h"
#include "Utils/CollisionManager.h"
#include "Utils/Core.h"
#include "Utils/DebugInfo.h"
#include "Utils/GameManager.h"
#include "Utils/InputHandler.h"
#include "Utils/Screen2DManager.h"
#include "raylib.h"
#include <iostream>

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
    DebugInfo* debugInfo = new DebugInfo();
    inputHandler->addDebugInfo(*debugInfo);                // add debugInfo to inputHandler
                                                           // instance of DebugInfo
    GameManager& gameManager = GameManager::getInstance(); // instance of GameObjectsManager

    gameManager.addInputHandler(inputHandler); // add inputHandler to gameManager
    inputHandler->addGameManager(gameManager); // add gameManager to inputHandler

    SetTargetFPS(Constants::FPS); // Set  game to run at X frames-per-second (recommended: 60)

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

    asepriteManager->loadAnimFile("barrel"); // asepriteManager.frameTags[barrel]
                                             // asepriteManager.textures[barrel]

    // Create Player 1
    BaseCharacter* player1 = new BaseCharacter(asepriteManager, Constants::PLAYER1_X, Constants::BASELINE);
    player1->setCurrentFrameTag("gbFighter-Idle"); // using gbFighter-Graphics
    player1->setObjName("Andy");
    player1->setPlayerNumber(1);
    player1->addController(inputHandler->getPlayer1Controller());
    player1->addCollisionBox("player1PushBox", 10, 0, 10, 30, CollisionBoxType::PUSHBOX, true, BLUE);
    player1->getStatemachine().changeState("Idle");

    // Create Player 2
    BaseCharacter* player2 = new BaseCharacter(asepriteManager, Constants::PLAYER2_X, Constants::BASELINE);
    player2->setCurrentFrameTag("nesFighter-Idle"); // using nesFighter-Graphics
    player2->setObjName("Ken");
    player2->setPlayerNumber(2);
    player2->addController(inputHandler->getPlayer2Controller());
    player2->addCollisionBox("player2PushBox", 16, 0, 10, 30, CollisionBoxType::PUSHBOX, true, BLUE);
    player2->getStatemachine().changeState("Idle");

    // TODO: get rid of this - just for testing
    // Create a BaseGameObject with a barrel Sprite for testing
    unique<BaseGameObject> barrel = std::make_unique<BaseGameObject>(asepriteManager, 20, 142);
    barrel->setCurrentFrameTag("barrel-Idle");
    barrel->setObjName("Barrel");
    barrel->addCollisionBox("Collisionbox", 10, 10, 10, 10, CollisionBoxType::HITBOX, true, RED);


    // Add the player1 and player2 to the gameManager
    gameManager.addBaseCharacter("player1", player1);
    gameManager.addBaseCharacter("player2", player2);
    gameManager.addBaseGameObject(barrel.get());

    // Create Static Background
    Texture2D stage = LoadTexture("Assets/Graphics/stage.png");


    gameManager
        .init(); // initialize gameManager (can only be done after all gameObjects are added and must be at the end)


#ifdef DEBUG
    debugInfo->addGameObject("Player1", player1);
    debugInfo->addGameObject("Player2", player2);
    debugInfo->addGameObject(
        "Barrel",
        barrel.get()); // dangerous, because the unique pointer is not copied //TODO: get rid of this
#endif

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        deltaTime = GetFrameTime(); // update global Variable deltaTime

        //----------------------------------------------------------------------------------
        // Update
        //----------------------------------------------------------------------------------

        // TODO: uncoment and refactor update of screen2DManager
        //screen2DManager->update(deltaTime);

        // Handle Input (by calling the update method of the inputHandler)
        inputHandler->Update();

        // Update gameObjects (player1 and player2 included)
        gameManager.update(deltaTime);

        //----------------------------------------------------------------------------------
        // Draw to RenderTexture
        //----------------------------------------------------------------------------------

        // BeginTextureMode(target);
        screen2DManager->beginDrawToRenderTarget("mainRenderTarget");

        ClearBackground(RAYWHITE);

        // draw stage
        float stage_scale = 1.f;
        DrawTextureEx(stage, {0, 80}, 0, stage_scale, WHITE);

        // draw gameObjects (player1 and player2 included)
        gameManager.draw();

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

        // Draw a black outlined rectangle around the mainView
        DrawRectangleLinesEx(Rectangle{0, 0, 1540, 1070}, 6, BLACK);
        // Draw a second black outlined rectangle on the right side of the screen
        DrawRectangleLinesEx(Rectangle{1545, 0, 374, 1070}, 6, BLACK);


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
