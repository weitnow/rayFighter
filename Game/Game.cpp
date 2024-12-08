#include "Game.h"
#include "../Utils/HelperFunctions.h" // for initializeRandom

Game::Game() : quit(false)
{

    // Initialize random seed once
    Utils::
        initializeRandom(); // defined in HelperFunctions.h, used to seed the random number generator for getRandomValueOf

    // Managing Global Compontents - which will be used in all game states
    // Initialize screen2DManager and set window size and title, this has to be done first before everything else
    screen2DManager = new Screen2DManager(ScreenResolution::S_1920x1080,
                                          "C++ RayFighter",
                                          RenderResolution::R_1280x720); // instance of Screen2DManager


    screen2DManager->changeScreenResolution(ScreenResolution::S_1920x1080); // set the screen resolution

    soundManager = &SoundManager::getInstance();
    inputHandler = new InputHandler();
    asepriteManager = new AsepriteManager{"Assets/Graphics/"}; // instance of AsepriteManager
    asepriteManager->init();
    screen2DManager->takeReferenceToAsepriteManager(asepriteManager); // load all aseprite files
    deltaTime = GetFrameTime(); // will be feed in the update method of the different game states

    screen2DManager->loadScreenGenericEffects(
        "screenEffects"); // load the screenEffects animation file, the screenManager will unload it in the destructor
}

Game::~Game()
{

    std::cout << "Game Destructor called, unloading resources" << std::endl;

    delete screen2DManager; //deallocate memory on the heap
    delete inputHandler;    //deallocate memory on the heap
    delete asepriteManager; //deallocate memory on the heap

    // soundManager is a singleton and will be deleted automatically
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
        currentState->Update(deltaTime);
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
