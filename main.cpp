#include "Characters/Fighter1.h"
#include "Characters/Fighter2.h"
#include "Constants.h"
#include "GameObjects/BaseGameObject.h"
#include "GameObjects/Items/Barrel.h"
#include "Utils/AsepriteManager.h"
#include "Utils/CollisionManager.h"
#include "Utils/Core.h"
#include "Utils/DebugInfo.h"
#include "Utils/GameManager.h"
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
    // Initialize screen2DManager and set window size and title, this has to be done first before everything else
    Screen2DManager* screen2DManager =
        new Screen2DManager(Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT, "C++ gbFighter");

    SoundManager& soundManager = SoundManager::getInstance();
    InputHandler* inputHandler = new InputHandler();
    float deltaTime; // global variable - will be updated in the main game loop
    AsepriteManager* asepriteManager = new AsepriteManager{"Assets/Graphics/"}; // instance of AsepriteManager
    DebugInfo* debugInfo = new DebugInfo();                                     // instance of DebugInfo
    inputHandler->addDebugInfo(*debugInfo);                                     // add debugInfo to inputHandler
    GameManager& gameManager = GameManager::getInstance();                      // instance of GameObjectsManager
    gameManager.addInputHandler(inputHandler);                                  // add inputHandler to gameManager
    inputHandler->addGameManager(gameManager);                                  // add gameManager to inputHandler
    asepriteManager->init();                                                    // load all aseprite files
    gameManager.addAsepriteManager(asepriteManager);                            // add asepriteManager to gameManager


    SetTargetFPS(Constants::FPS); // Set  game to run at X frames-per-second (recommended: 60)

    // Set the resolution/size of the of the renderTarget (not the screen resolution), default is 1120x630
    // screen2DManager->setResolution(Resolution::R_1920x1080);
    // screen2DManager->setResolution(Resolution::R_2560x1440);

    // Create Player 1 and 2
    Fighter1* player1 = new Fighter1(asepriteManager, Constants::PLAYER1_X, Constants::BASELINE);
    Fighter2* player2 = new Fighter2(asepriteManager, Constants::PLAYER2_X, Constants::BASELINE);

    // TODO: get rid of this - just for testing
    // Create a BaseGameObject with a barrel Sprite for testing
    unique<Barrel> barrel = std::make_unique<Barrel>(asepriteManager, 20, 102);
    barrel->setCurrentFrameTag("barrel-Idle");
    barrel->setObjName("Barrel");
    barrel->addCollisionBoxForFrame("barrel-Idle", -1, CollisionBoxType::HURTBOX, true, 10, 10, 13, 17);

    // Add the player1 and player2 and gameobjects to the gameManager
    gameManager.addBaseCharacter("player1", player1);
    gameManager.addBaseCharacter("player2", player2);
    gameManager.addBaseGameObject(barrel.get());

    // Initialize Player 1 and Player 2 (needs to be done after adding them to the gameManager, otherwise the getBaseCharacter methode of GameManager which is Used in State.cpp will return a nullptr)
    player1->init();
    player2->init();

    gameManager
        .init(); // initialize gameManager (can only be done after all gameObjects are added and must be at the end)

#ifdef DEBUG_WINDOW
    debugInfo->addGameObject("Player1", player1);
    debugInfo->addGameObject("Player2", player2);
    debugInfo->addGameObject(
        "Barrel",
        barrel.get()); // dangerous, because the unique pointer is not copied //TODO: get rid of this
#endif

    // Start playing background music
    if (Constants::BACKGROUND_MUSIC)
    {
        soundManager.playRandomBackgroundMusic();
    }

    // TODO: refactor this
    /* #region select a background by random*/
    std::vector<std::string> backgrounds = {"stage-factory",
                                            "stage-desert",
                                            "stage-outworld",
                                            "stage-park",
                                            "stage-laboratory",
                                            "stage-temple",
                                            "stage-shaolin",
                                            "stage-pyramid",
                                            "stage-city",
                                            "stage-boulevard",
                                            "stage-jungle",
                                            "stage-wushu",
                                            "stage-london",
                                            "stage-ricefield",
                                            "stage-ring"};
    // Seed the random number generator
    std::srand(static_cast<unsigned>(std::time(0)));
    // Generate a random index between 0 and backgrounds.size() - 1
    int randomIndex = std::rand() % backgrounds.size();
    // Select a random background
    std::string randomBackground = backgrounds[randomIndex];
    /* #endregion */

    AsepriteAnimationFile* background = asepriteManager->getAnimFile("stage");

    // TEST
    float camPos = 0;

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        deltaTime = GetFrameTime(); // update global Variable deltaTime

        //----------------------------------------------------------------------------------
        // Update
        //----------------------------------------------------------------------------------

        screen2DManager->update(deltaTime * Constants::TIME_MULTIPLIER); // update camera

        // Handle Input (by calling the update method of the inputHandler)
        inputHandler->Update();

        // Update gameObjects (player1 and player2 included)
        gameManager.update(deltaTime * Constants::TIME_MULTIPLIER);

        // Update Music
        soundManager.updateBackgroundMusic();

        //----------------------------------------------------------------------------------
        // Draw to RenderTexture
        //----------------------------------------------------------------------------------
        // BeginTextureMode(target);
        screen2DManager->beginDrawToRenderTarget();

        ClearBackground(RAYWHITE);


        // calculate Camera
        float& middlepointX = gameManager.middlePointXbetweenPlayers;

        if (middlepointX < 105.f)
        {
            camPos = camPos - 50 * deltaTime;
            player1->setCamVector(Vector2{50.f, 0.f});
            player2->setCamVector(Vector2{50.f, 0.f});
        }
        else if (middlepointX > 152.f)
        {
            // move background to the left
            camPos = camPos + 50 * deltaTime;
            player1->setCamVector(Vector2{-50.f, 0.f});
            player2->setCamVector(Vector2{-50.f, 0.f});
        }
        else
        {
            // don't move anything
            player1->resetCamVector();
            player2->resetCamVector();
        }

        screen2DManager->camera.target.x = camPos;


        // Begin the camera
        BeginMode2D(screen2DManager->camera);

        // draw stage
        float stage_scale = 1.f;

        background->drawFrame(randomBackground, 0 - Constants::BACKGROUND_WIDTH, 40, stage_scale, WHITE);
        background->drawFrame(randomBackground, 0, 40, stage_scale, WHITE);
        background->drawFrame(randomBackground, 0 + Constants::BACKGROUND_WIDTH, 40, stage_scale, WHITE);

        // End the camera
        EndMode2D();

        // draw gameObjects (player1 and player2 included)
        gameManager.draw();


        screen2DManager->endDrawToRenderTarget();
        //----------------------------------------------------------------------------------
        // Draw to Screen
        //----------------------------------------------------------------------------------
        screen2DManager->beginDrawToScreen();

        ClearBackground(GREEN);

        // Draw RenderTexture to Screen
        screen2DManager->drawRenderTarget();

#ifdef DEBUG_WINDOW
        // Draw a black outlined rectangle around the mainView
        DrawRectangleLinesEx(Rectangle{0, 0, 1540, 1070}, 6, BLACK);
        // Draw a second black outlined rectangle on the right side of the screen
        DrawRectangleLinesEx(Rectangle{1545, 0, 374, 1070}, 6, BLACK);
#endif

#ifdef DEBUG_WINDOW
        debugInfo->draw();
#endif

        screen2DManager->endDrawToScreen();
    }
    //----------------------------------------------------------------------------------
    // De-Initialization
    //--------------------------------------------------------------------------------------

    delete player1;
    delete player2;

    screen2DManager->unloadRenderTarget();
    delete screen2DManager; //deallocate memory on the heap
    delete inputHandler;    //deallocate memory on the heap
    delete asepriteManager; //deallocate memory on the heap
    delete debugInfo;       //deallocate memory on the heap
    delete background;      //deallocate memory on the heap

    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
