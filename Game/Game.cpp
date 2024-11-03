#include "Game.h"

Game::Game() : quit(false)
{
    // Managing Global Compontents
    // Initialize random seed once
    initializeRandom(); // defined in HelperFunctions.h, used to seed the random number generator for getRandomValueOf

    // Initialize screen2DManager and set window size and title, this has to be done first before everything else
    screen2DManager = new Screen2DManager(Constants::SCREEN_WIDTH,
                                          Constants::SCREEN_HEIGHT,
                                          "C++ gbFighter",
                                          false,
                                          Resolution::R_1120x630);

    soundManager = &SoundManager::getInstance();
    inputHandler = new InputHandler();
    asepriteManager = new AsepriteManager{"Assets/Graphics/"}; // instance of AsepriteManager
    debugInfo = new DebugInfo();                               // instance of DebugInfo
    inputHandler->addDebugInfo(*debugInfo);                    // add debugInfo to inputHandler
    gameManager = &GameManager::getInstance();                 // instance of GameObjectsManager
    gameManager->addInputHandler(inputHandler);                // add inputHandler to gameManager
    gameManager->addGameInstance(this);                        // add game to gameManager
    inputHandler->addGameManager(*gameManager);                // add gameManager to inputHandler
    asepriteManager->init();                                   // load all aseprite files
    gameManager->addAsepriteManager(asepriteManager);          // add asepriteManager to gameManager
    screen2DManager->init();                                   // setFPS and setSize of the renderTarget

    // Create Player 1 and 2
    player1 = new Fighter1(asepriteManager, Constants::PLAYER1_X, Constants::BASELINE);
    player2 = new Fighter2(asepriteManager, Constants::PLAYER2_X, Constants::BASELINE);

    // TODO: get rid of this - just for testing
    // Create a BaseGameObject with a barrel Sprite for testing
    barrel = std::make_unique<Barrel>(asepriteManager, 20, 102);
    barrel->setCurrentFrameTag("barrel-Idle");
    barrel->setObjName("Barrel");
    barrel->addCollisionBoxForFrame("barrel-Idle", -1, CollisionBoxType::HURTBOX, true, 10, 10, 13, 17);

    // Add the player1 and player2 and gameobjects to the gameManager
    gameManager->addBaseCharacter("player1", player1);
    gameManager->addBaseCharacter("player2", player2);
    gameManager->addBaseGameObject(barrel.get());

    // Initialize Player 1 and Player 2 (needs to be done after adding them to the gameManager, otherwise the getBaseCharacter methode of GameManager which is Used in State.cpp will return a nullptr)
    player1->init();
    player2->init();

    gameManager
        ->init(); // initialize gameManager (can only be done after all gameObjects are added and must be at the end)


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

    randomBackground = getRandomValueOf(backgrounds);

    background = asepriteManager->getAnimFile("stage");
    deltaTime = GetFrameTime();
    camPos = 0;
}

Game::~Game()
{
    // Deleting Global Components
    delete player1;
    delete player2;

    screen2DManager->unloadRenderTarget();
    delete screen2DManager; //deallocate memory on the heap
    delete inputHandler;    //deallocate memory on the heap
    delete asepriteManager; //deallocate memory on the heap
    delete debugInfo;       //deallocate memory on the heap
    delete background;      //deallocate memory on the heap
}

void Game::ChangeState(std::unique_ptr<BaseState> newState)
{
    if (currentState)
    {
        currentState->Exit();
    }
    currentState = std::move(newState);
    currentState->Enter();
}

void Game::Update()
{
    deltaTime = GetFrameTime();
    if (currentState)
    {
        currentState->Update();
    }
}

void Game::Render()
{
    if (currentState)
    {
        currentState->Render();
    }
}
