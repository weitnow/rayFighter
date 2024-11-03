#include "Game.h"
#include "../Utils/HelperFunctions.h" // for initializeRandom

Game::Game() : quit(false)
{

    // Initialize random seed once
    initializeRandom(); // defined in HelperFunctions.h, used to seed the random number generator for getRandomValueOf

    // Managing Global Compontents - which will be used in all game states
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
    //gameManager->addAsepriteManager(asepriteManager);          // add asepriteManager to gameManager
    screen2DManager->init(); // setFPS and setSize of the renderTarget

    deltaTime = GetFrameTime(); // will be feed in the update method of the different game states
}

Game::~Game()
{
    screen2DManager->unloadRenderTarget();
    delete screen2DManager; //deallocate memory on the heap
    delete inputHandler;    //deallocate memory on the heap
    delete asepriteManager; //deallocate memory on the heap
    delete debugInfo;       //deallocate memory on the heap
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
    else
    {
        throw std::runtime_error("Game.cpp: currentState is nullptr");
    }
}

void Game::Render()
{
    if (currentState)
    {
        currentState->Render();
    }
}
