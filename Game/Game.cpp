#include "Game.h"
#include "../Utils/HelperFunctions.h" // for initializeRandom

Game::Game() : quit(false)
{
    // Initialize random seed once
    Utils::
        initializeRandom(); // defined in HelperFunctions.h, used to seed the random number generator for getRandomValueOf

    // Managing Global Compontents - which will be used in all game states
    // Initialize screen2DManager and set window size and title, this has to be done first before everything else
    screen2DManager = std::make_unique<Screen2DManager>("C++ RayFighter"); //instance of Screen2DManager

    if (!screen2DManager->loadScreenResolution()) //load screenresolution from file
    {
        // if it could not have been loaded use 1280 x 720 resolution as default
        screen2DManager->changeScreenResolution(ScreenResolution::S_1280x720); // set the screen resolution
    }
    soundManager = &SoundManager::getInstance();

    // Load Configuration from file /Data/*
    screen2DManager->loadScreenResolution();
    soundManager->loadSoundConfig();

    inputHandler = std::make_unique<InputHandler>();
    asepriteManager = std::make_unique<AsepriteManager>("Assets/Graphics/"); // instance of AsepriteManager
    asepriteManager->init();
    screen2DManager->takeReferenceToAsepriteManager(asepriteManager.get()); // load all aseprite files
    deltaTime = GetFrameTime(); // will be feed in the update method of the different game states

    screen2DManager->loadScreenGenericEffects(
        "screenEffects"); // load the screenEffects animation file, the screenManager will unload it in the destructor

    HideCursor(); // Raylibfunction to hide the Mousecursor
}

Game::~Game()
{

    std::cout << "Game Destructor called, unloading resources" << std::endl;

    // Ensure the stack is cleard
    while (!stateStack.empty())
    {
        stateStack.top()->Exit();
        stateStack.pop();
    }

    // soundManager is a singleton and will be deleted automatically
}

void Game::init()
{
    player1 = 0;
    player2 = 0;
    selectedStage = 0;
}

void Game::ChangeState(std::unique_ptr<BaseState> newState)
{
    if (!stateStack.empty())
    {
        stateStack.top()->Exit(); // Finalize the current state
        stateStack.pop();         // Remove it from the stack
    }
    stateStack.push(std::move(newState));
    stateStack.top()->Enter(); // Initialize the new state
}

void Game::PushState(std::unique_ptr<BaseState> newState)
{
    if (!stateStack.empty())
    {
        stateStack.top()->Pause();
    }
    stateStack.push(std::move(newState));
    stateStack.top()->Enter(); // Initialize the new state
}

void Game::PopState()
{
    if (!stateStack.empty())
    {
        stateStack.top()->Exit(); // Finalize the current state
        stateStack.pop();         // Remove it from the stack
    }
    if (!stateStack.empty())
    {
        stateStack.top()->Resume();
    }
}

void Game::Update()
{
    deltaTime = GetFrameTime();

    inputHandler->Update(); //update player1Controller/player2Controller

    soundManager->updateBackgroundMusic(); // Update the background music

    screen2DManager->update(deltaTime); // Update the screen2DManager

    if (!stateStack.empty())
    {
        stateStack.top()->Update(deltaTime);
    }

    HandleInput(); // Handle general input
}

void Game::HandleInput()
{
    // Handle general input, valid in every state
    if (WindowShouldClose()) // Check if the window close button is clicked or 1 is pressed
    {
        quit = true;

        // Ensure all states exit properly
        while (!stateStack.empty())
        {
            stateStack.top()->Exit();
            stateStack.pop();
        }
    }
}


void Game::Render()
{
    if (!stateStack.empty())
    {
        stateStack.top()->Render();
    }
}
