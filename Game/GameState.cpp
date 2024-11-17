#include "GameState.h"
#include "../Characters/Fighter1.h"
#include "../Characters/Fighter2.h"
#include "../Utils/HelperFunctions.h"
#include "Game.h"


GameState::GameState(Game* game) : BaseState(game), camPos{0}
{
    debugInfo = new DebugInfo(this);        // instance of DebugInfo
    inputHandler->addDebugInfo(*debugInfo); // add debugInfo to inputHandler


    // Create Player 1 and 2
    player1 = new Fighter1(asepriteManager, Constants::PLAYER1_X, Constants::BASELINE);
    player2 = new Fighter2(asepriteManager, Constants::PLAYER2_X, Constants::BASELINE);


    player1->addController(game->inputHandler->getPlayer1Controller());
    player1->init();

    player2->addController(game->inputHandler->getPlayer2Controller());
    player2->init();

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

    randomBackground = Utils::getRandomValueOf(backgrounds);

    background = asepriteManager->getAnimFile("stage");


    if (player1 == nullptr || player2 == nullptr)
    {
        throw std::runtime_error("GameState::GameState -> player1 or player2 is nullptr");
    }
}

GameState::~GameState()
{
    if (Constants::BACKGROUND_MUSIC)
    {
        game->soundManager->unloadMusic("ken.wav");
    }

    // Deleting Global Components
    delete debugInfo;

    delete player1;
    delete player2;

    delete background; //deallocate memory on the heap
}

void GameState::Enter()
{
    BaseState::Enter();

    // Start playing random background music
    if (Constants::BACKGROUND_MUSIC)
    {
        game->soundManager->loadMusic("ken.wav", 0.8f);
        game->soundManager->playBackgroundMusic("ken.wav");
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

    // calculate middlePointXbetweenPlayers
    middlePointXbetweenPlayers = (player1->getPos().x + player2->getPos().x + 32) / 2.f;

    game->soundManager->updateBackgroundMusic(); // Update Music}
}

void GameState::Render()
{

    //----------------------------------------------------------------------------------
    // Draw to RenderTexture
    //----------------------------------------------------------------------------------
    // BeginTextureMode(target);
    game->screen2DManager->beginDrawToRenderTarget();

    ClearBackground(RAYWHITE);


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


    // Begin the camera
    BeginMode2D(game->screen2DManager->camera);

    // draw stage
    float stage_scale = 1.f;

    background->drawFrame(randomBackground, 0 - Constants::BACKGROUND_WIDTH, 40, stage_scale, WHITE);
    background->drawFrame(randomBackground, 0, 40, stage_scale, WHITE);
    background->drawFrame(randomBackground, 0 + Constants::BACKGROUND_WIDTH, 40, stage_scale, WHITE);

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

    // Draw a white rectangle for UpperGui
    DrawRectangle(0, 0, 256, 40, WHITE);

    // Draw the HUD
    //hud->Draw();

    if (Global::debugMode)
    {
        // Draw the middlePointXbetweenPlayers
        DrawLine(middlePointXbetweenPlayers, 0, middlePointXbetweenPlayers, 300, RED);
    }


    game->screen2DManager->endDrawToRenderTarget();
    //----------------------------------------------------------------------------------
    // Draw to Screen
    //----------------------------------------------------------------------------------
    game->screen2DManager->beginDrawToScreen();

    ClearBackground(GREEN);

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
