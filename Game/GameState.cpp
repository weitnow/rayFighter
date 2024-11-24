#include "GameState.h"
#include "../Characters/Fighter1.h"
#include "../Characters/Fighter2.h"
#include "../Constants.h"
#include "../Utils/HelperFunctions.h"
#include "Game.h"


GameState::GameState(Game* game) : BaseState(game), camPos{0}
{
    debugInfo = new DebugInfo(this);        // instance of DebugInfo
    inputHandler->addDebugInfo(*debugInfo); // add debugInfo to inputHandler

    // Create the HUD
    gui = new Gui(game);


    // Create Player 1 and 2
    player1 = new Fighter1(asepriteManager, Constants::PLAYER1_X, Constants::BASELINE);
    player2 = new Fighter2(asepriteManager, Constants::PLAYER2_X, Constants::BASELINE);


    player1->addController(game->inputHandler->getPlayer1Controller());
    player1->init();

    player2->addController(game->inputHandler->getPlayer2Controller());
    player2->init();


    randomBackground = "stages-Stage1";

    background = asepriteManager->getAnimFile("stages");


    if (player1 == nullptr || player2 == nullptr)
    {
        throw std::runtime_error("GameState::GameState -> player1 or player2 is nullptr");
    }
}

GameState::~GameState()
{
    if (Constants::BACKGROUND_MUSIC)
    {
        game->soundManager->unloadMusic("asia.mp3");
    }

    // Deleting Global Components
    delete debugInfo;

    delete player1;
    delete player2;

    delete gui;

    delete background; //deallocate memory on the heap
}

void GameState::Enter()
{
    BaseState::Enter();

    // Start playing random background music
    if (Constants::BACKGROUND_MUSIC)
    {
        game->soundManager->loadMusic("asia.mp3", 0.8f);
        game->soundManager->playBackgroundMusic("asia.mp3");
    }
}


void GameState::Update(float deltaTime)
{
    game->inputHandler->Update(); // Handle Input

    _updateIsLeftPlayer1and2(); // Check if player1 is left of player2

    _checkHitsBetweenPlayers(); // Check if player1 and player2 are hitting each other

    // Update all gameObjects
    for (auto& object : gameObjects)
    {
        object->update(deltaTime);
    }

    // Update all baseCharacters
    for (auto& object : baseCharacters)
    {
        object->update(deltaTime);
    }

    // Update players
    player1->update(deltaTime);
    player2->update(deltaTime);

    _checkCollisionsBetweenPlayers();

    game->soundManager->updateBackgroundMusic(); // Update Music}

    // calculate middlePointXbetweenPlayers (needed for _updateCamera)
    middlePointXbetweenPlayers = (player1->getPos().x + player2->getPos().x + 32) / 2.f;

    // calculate middlePointYbetweenPlayers (NOT needed for _updateCamera)
    middlePointYbetweenPlayers = (player1->getPos().y + player2->getPos().y) / 2.f;

    _updateCamera();
    _updateBackground();

    // Update the HUD
    gui->update(deltaTime);
}

void GameState::Render()
{
    //----------------------------------------------------------------------------------
    // Draw to RenderTexture
    //----------------------------------------------------------------------------------
    // BeginTextureMode(target);
    game->screen2DManager->beginDrawToRenderTarget();

    ClearBackground(WHITE);

    // Begin the camera
    BeginMode2D(game->screen2DManager->camera);

    // draw stage
    background->drawFrame(randomBackground, -80 + BackgroundOffsetX, 24 + BackgroundOffsetY, 1, WHITE);


    // End the camera
    EndMode2D();

    // draw gameObjects (player1 and player2 included)
    // Draw all gameObjects
    for (auto& object : gameObjects)
    {
        object->draw();
    }

    // Draw all baseSpriteObjects
    for (auto& object : baseSpriteObjects)
    {
        object->draw();
    }

    // Draw all baseCharacters
    for (auto& object : baseCharacters)
    {
        object->draw();
    }

    // draw player 1 and 2
    player1->draw();
    player2->draw();

    // Draw the GUI
    gui->draw();

    if (Global::debugMode)
    {
        // Draw the middlePointXbetweenPlayers
        DrawLine(middlePointXbetweenPlayers, 0, middlePointXbetweenPlayers, 300, RED);
        // Draw the middlePointYbetweenPlayers
        DrawLine(0, middlePointYbetweenPlayers, 256, middlePointYbetweenPlayers, RED);
    }


    game->screen2DManager->endDrawToRenderTarget();
    //----------------------------------------------------------------------------------
    // Draw to Screen
    //----------------------------------------------------------------------------------
    game->screen2DManager->beginDrawToScreen();

    ClearBackground(Constants::RAYFIGHTER_LIGHTROSA);

    // Draw RenderTexture to Screen
    game->screen2DManager->drawRenderTarget();

    if (Global::debugWindow)
    {
        // Draw a black outlined rectangle around the mainView
        DrawRectangleLinesEx(Rectangle{0, 0, 1540, 1070}, 6, BLACK);
        // Draw a second black outlined rectangle on the right side of the screen
        DrawRectangleLinesEx(Rectangle{1545, 0, 374, 1070}, 6, BLACK);

        debugInfo->draw();
    }
    game->screen2DManager->endDrawToScreen();
}

void GameState::Exit()
{
}


void GameState::_updateIsLeftPlayer1and2()
{
    // check wheter player 1 is left of player 2
    if (player1->getPos().x < player2->getPos().x)
    {
        player1->setIsLeft(true);
        player2->setIsLeft(false);
    }
    else
    {
        player1->setIsLeft(false);
        player2->setIsLeft(true);
    }
}

void GameState::_checkCollisionsBetweenPlayers()
{
    // Check if player1 and player2 are colliding
    // TODO: get rid of hardcoded [0]
    CollisionBox2D player1PushBox = player1->getPushBoxes()[0];
    CollisionBox2D player2PushBox = player2->getPushBoxes()[0];

    if (Utils::checkCollision(player1PushBox, player2PushBox))
    {
        // Handle collision (you can define specific collision logic here)
        if (player1->getIsLeft())
        {
            player1->setPushVector({-50, 0});
            player2->setPushVector({50, 0});
        }
        else
        {
            player1->setPushVector({50, 0});
            player2->setPushVector({-50, 0});
        }
    }
}

void GameState::_checkHitsBetweenPlayers()
{
    // TODO: refactor this, this stuff must be in the statemachine
    // loop through all hitboxes of player1
    for (auto& hitbox : player1->getHitBoxes())
    {
        // loop through all hurtboxes of player2
        for (auto& hurtbox : player2->getHurtBoxes())
        {
            if (Utils::checkCollision(hitbox, hurtbox) && player1->canDealDamage)
            {
                // Handle hit (you can define specific hit logic here)
                player2->takeDamage(1, &hitbox);
                if (player1->getCurrentState() == "Kick")
                {
                    player2->setPushVector({200, 0});
                }
                else if (player1->getCurrentState() == "Punch")
                {
                    player2->setPushVector({120, 0});
                }

                player1->canDealDamage = false;

                SoundManager::getInstance().playSound("mk2/punchSound.mp3");
            }
        }
    }

    // loop through all hitboxes of player2
    for (auto& hitbox : player2->getHitBoxes())
    {
        // loop through all hurtboxes of player1
        for (auto& hurtbox : player1->getHurtBoxes())
        {
            if (Utils::checkCollision(hitbox, hurtbox) && player2->canDealDamage)
            {
                // Handle hit (you can define specific hit logic here)
                player1->takeDamage(1, &hitbox);
                player2->canDealDamage = false;

                SoundManager::getInstance().playSound("mk2/punchSound.mp3");
            }
        }
    }
}

void GameState::_updateCamera()
{
    if (middlePointXbetweenPlayers < 105.f)
    {
        camPos = camPos - 50 * game->deltaTime;
        player1->setCamVector(Vector2{50.f, 0.f});
        player2->setCamVector(Vector2{50.f, 0.f});
    }
    else if (middlePointXbetweenPlayers > 152.f)
    {
        // move background to the left
        camPos = camPos + 50 * game->deltaTime;
        player1->setCamVector(Vector2{-50.f, 0.f});
        player2->setCamVector(Vector2{-50.f, 0.f});
    }
    else
    {
        // don't move anything
        player1->resetCamVector();
        player2->resetCamVector();
    }

    game->screen2DManager->camera.target.x = camPos;
}

void GameState::_updateBackground()
{

    // scroll background in Y direction

    //Baseline is 102 = BackgroundOffsetY is 0 (neutral)
    //everything less must be negative
    //everything more must be positive

    BackgroundOffsetY = (102 - middlePointYbetweenPlayers) * 0.2f;

    std::cout << "BackgroundOffsetY: " << BackgroundOffsetY << std::endl;
}
