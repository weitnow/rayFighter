#include "Characters/BaseCharacter.h"
#include "Characters/Fighter_Andi.h"
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

    // Initialize SoundManager
    SoundManager& soundManager = SoundManager::getInstance();

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

    asepriteManager->getFrameTag("gbFighter-Death").loop = false; // set loop to false for the death animation


    asepriteManager->loadAnimFile("nesFighter"); // asepriteManager.frameTags[nesFighter-Idle]
                                                 // asepriteManager.textures[nesFighter]

    asepriteManager->getFrameTag("nesFighter-Death").loop = false; // set loop to false for the death animation

    asepriteManager->loadAnimFile("bgAnimation"); // asepriteManager.frameTags[bgAnimation]
                                                  // asepriteManager.textures[bgAnimation]

    asepriteManager->loadAnimFile("barrel"); // asepriteManager.frameTags[barrel]
                                             // asepriteManager.textures[barrel]

    asepriteManager->loadAnimFile("stage"); // asepriteManager.frameTags[stage-temple]
                                            // asepriteManager.textures[stage]

    asepriteManager->loadAnimFile("deadSkull");

    // Add asepriteManager to gameManager
    gameManager.addAsepriteManager(asepriteManager); // add asepriteManager to gameManager

    // Create Player 1
    BaseCharacter* player1 = new BaseCharacter(asepriteManager, Constants::PLAYER1_X, Constants::BASELINE);

    // Create Player 2
    BaseCharacter* player2 = new BaseCharacter(asepriteManager, Constants::PLAYER2_X, Constants::BASELINE);

    // TODO: get rid of this - just for testing
    // Create a BaseGameObject with a barrel Sprite for testing
    unique<Barrel> barrel = std::make_unique<Barrel>(asepriteManager, 20, 142);
    barrel->setCurrentFrameTag("barrel-Idle");
    barrel->setObjName("Barrel");
    barrel->addCollisionBoxForFrame("barrel-Idle", -1, CollisionBoxType::HURTBOX, true, 10, 10, 13, 17);

    // Add the player1 and player2 to the gameManager
    gameManager.addBaseCharacter("player1", player1);
    gameManager.addBaseCharacter("player2", player2);
    gameManager.addBaseGameObject(barrel.get());

    // Initialize Player 1 and Player 2 (needs to be done after adding them to the gameManager, otherwise the getBaseCharacter methode of GameManager which is Used in State.cpp will return a nullptr)
    // Player 1
    player1->setCurrentFrameTag("gbFighter-Idle"); // using gbFighter-Graphics
    player1->setObjName("Andy");
    player1->setPlayerNumber(1);
    player1->addController(inputHandler->getPlayer1Controller());
    // [0, 1, 2...] = frameNumber, -1 = valid for all frames of the frameTagName, -2 = valid for all frames of the frameTagName
    player1->addCollisionBoxForFrame("gbFighter-Idle", -1, CollisionBoxType::PUSHBOX, true, 10, 0, 10, 30);
    player1->addCollisionBoxForFrame("gbFighter-Punch", 1, CollisionBoxType::HITBOX, true, 26, 10, 5, 5);
    player1->addCollisionBoxForFrame("gbFighter-Kick", 1, CollisionBoxType::HITBOX, true, 26, 10, 5, 5);
    player1->addCollisionBoxForFrame("gbFighter-JumpPunch", 0, CollisionBoxType::HITBOX, true, 24, 20, 5, 5);
    player1->addCollisionBoxForFrame("gbFighter-Idle",
                                     -2,
                                     CollisionBoxType::HURTBOX,
                                     HurtboxType::BODY,
                                     true,
                                     10,
                                     4,
                                     12,
                                     26);
    player1->getStatemachine().changeState("Walk");


    // Player 2
    player2->setLife(2);                            // Todo: get rid of setLife
    player2->setCurrentFrameTag("nesFighter-Idle"); // using nesFighter-Graphics
    player2->setObjName("Ken");
    player2->setPlayerNumber(2);
    player2->addController(inputHandler->getPlayer2Controller());
    player2->addCollisionBoxForFrame("nesFighter-Idle", -1, CollisionBoxType::PUSHBOX, true, 16, 0, 10, 30);
    player2->addCollisionBoxForFrame("nesFighter-Punch", 0, CollisionBoxType::HITBOX, true, 0, 15, 5, 5);
    player2->addCollisionBoxForFrame("nesFighter-Idle",
                                     -2,
                                     CollisionBoxType::HURTBOX,
                                     HurtboxType::BODY,
                                     true,
                                     16,
                                     0,
                                     10,
                                     25);
    player2->getStatemachine().changeState("Idle");

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
        screen2DManager->beginDrawToRenderTarget("mainRenderTarget");

        ClearBackground(RAYWHITE);

        // Begin the camera
        BeginMode2D(screen2DManager->camera);

        // draw stage
        float stage_scale = 1.f;
        background->drawFrame(randomBackground, 0, 80, stage_scale, WHITE);

        // draw gameObjects (player1 and player2 included)
        gameManager.draw();

        // End the camera
        EndMode2D();

        screen2DManager->endDrawToRenderTarget();
        //----------------------------------------------------------------------------------
        // Draw to Screen
        //----------------------------------------------------------------------------------
        screen2DManager->beginDrawToScreen();

        ClearBackground(GREEN);

        // Draw RenderTexture to Screen
        screen2DManager->drawRenderTarget("mainRenderTarget");

        // Draw a black outlined rectangle around the mainView
        DrawRectangleLinesEx(Rectangle{0, 0, 1540, 1070}, 6, BLACK);
        // Draw a second black outlined rectangle on the right side of the screen
        DrawRectangleLinesEx(Rectangle{1545, 0, 374, 1070}, 6, BLACK);

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

    screen2DManager->unloadAllRenderTextures();
    delete screen2DManager; //deallocate memory on the heap
    delete inputHandler;    //deallocate memory on the heap
    delete asepriteManager; //deallocate memory on the heap
    delete debugInfo;       //deallocate memory on the heap
    delete background;      //deallocate memory on the heap

    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------


    return 0;
}
