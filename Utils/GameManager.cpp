#include "GameManager.h"
#include "../Gui/Lifebar.h"
#include "CollisionManager.h"
#include "SoundManager.h"

// Define the static member variable and pass the GameManager instance to the constructor
CollisionManager GameManager::collisionManager(GameManager::getInstance());

// Define the static method to get the single instance of the class
GameManager& GameManager::getInstance()
{
    static GameManager instance; // This instance will be created the first time this method is called
    return instance;
}

void GameManager::init()
{
    collisionManager.init();
}

// Private constructor definition
GameManager::GameManager()
    : player1(nullptr), player2(nullptr), player1and2set(false), lifebar1(nullptr), lifebar2(nullptr)
{
    lifebar1 = new Lifebar(Vector2{20, 32}, 5, 100, 3, GREEN, BLACK, "Player1");
    lifebar2 = new Lifebar(Vector2{130, 32}, 5, 100, 3, GREEN, BLACK, "Player2");
}

// Optionally, define the destructor
GameManager::~GameManager()
{
    // Clean up resources if necessary
    delete lifebar1;
    delete lifebar2;
    lifebar1 = nullptr;
    lifebar2 = nullptr;
}

void GameManager::_updateIsLeftPlayer1and2()
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

void GameManager::_checkCollisionsBetweenPlayers()
{
    // Check if player1 and player2 are set
    if (!player1and2set)
    {
        return;
    }

    // Check if player1 and player2 are colliding
    // TODO: get rid of hardcoded [0]
    CollisionBox2D player1PushBox = player1->getPushBoxes()[0];
    CollisionBox2D player2PushBox = player2->getPushBoxes()[0];

    if (collisionManager.checkCollision(player1PushBox, player2PushBox))
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

void GameManager::_checkHitsBetweenPlayers()
{
    // TODO: refactor this, this stuff must be in the statemachine
    // loop through all hitboxes of player1
    for (auto& hitbox : player1->getHitBoxes())
    {
        // loop through all hurtboxes of player2
        for (auto& hurtbox : player2->getHurtBoxes())
        {
            if (collisionManager.checkCollision(hitbox, hurtbox) && player1->canDealDamage)
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

                SoundManager::getInstance().playSound(SoundManager::getInstance().punchSound);
            }
        }
    }

    // loop through all hitboxes of player2
    for (auto& hitbox : player2->getHitBoxes())
    {
        // loop through all hurtboxes of player1
        for (auto& hurtbox : player1->getHurtBoxes())
        {
            if (collisionManager.checkCollision(hitbox, hurtbox) && player2->canDealDamage)
            {
                // Handle hit (you can define specific hit logic here)
                player1->takeDamage(1, &hitbox);
                player2->canDealDamage = false;

                SoundManager::getInstance().playSound(SoundManager::getInstance().punchSound);
            }
        }
    }
}

void GameManager::_setPlayer1and2()
{
    // Check if player1 and player2 are set
    if (player1and2set)
        return;

    for (const auto& pair : baseCharacters)
    {
        BaseCharacter* character = pair.second;

        if (character->getPlayerNumber() == 1)
        {
            player1 = character;
        }
        else if (character->getPlayerNumber() == 2)
        {
            player2 = character;
        }

        // Exit loop early if both players are found
        if (player1 != nullptr && player2 != nullptr)
        {
            break;
        }
    }

    if (!player1)
    {
        throw std::runtime_error("Error: player1 not found in baseCharacters map.");
    }

    if (!player2)
    {
        throw std::runtime_error("Error: player2 not found in baseCharacters map.");
    }

    player1and2set = true;
}

void GameManager::addBaseCharacter(const std::string& CharName, BaseCharacter* character)
{
    // check if the character already exists and if so, raise an error
    if (baseCharacters.find(CharName) != baseCharacters.end())
    {
        throw std::runtime_error("baseCharacter with CharName " + CharName +
                                 " already exists"
                                 "\n Cannot add it again. GameObjectsManager::addBaseCharacter");
        return;
    }


    baseCharacters[CharName] = character;
}

void GameManager::removeBaseCharacter(const std::string& CharName)
{
    baseCharacters.erase(CharName);
}

// Define the methods to manage game objects
void GameManager::addBaseGameObject(BaseGameObject* object)
{
    gameObjects.push_back(object);
}

void GameManager::removeBaseGameObject()
{
    // Implementation of removing an object
    throw std::runtime_error("GameManager::removeBaseGameObject -> Not implemented yet.");
}

void GameManager::addBaseSpriteObject(BaseSpriteObject* object)
{
    baseSpriteObjects.push_back(object);
}

void GameManager::removeBaseSpriteObject()
{
    // Implementation of removing an object
    throw std::runtime_error("GameManager::removeBaseSpriteObject -> Not implemented yet.");
}

void GameManager::update(float deltaTime)
{
    // Multiply deltaTime by deltaTimeMultiplier (can be used to speed up or slow down the game)
    deltaTime *= deltaTimeMultiplier;

    // Set player1 and player2 if not already set
    _setPlayer1and2();

    // Update isLeft for player1 and player2
    _updateIsLeftPlayer1and2();

    _checkHitsBetweenPlayers();

    // Update all gameObjects
    for (auto& object : gameObjects)
    {
        object->update(deltaTime);
    }

    // Update all baseCharacters
    for (auto& pair : baseCharacters)
    {
        pair.second->update(deltaTime);
    }

    // Update the collision manager
    collisionManager.update(deltaTime);

    _checkCollisionsBetweenPlayers();


    // Update the lifebars
    lifebar1->Update(player1->getCurrentLife());
    lifebar2->Update(player2->getCurrentLife());

    // calculate middlePointXbetweenPlayers
    middlePointXbetweenPlayers = (player1->getPos().x + player2->getPos().x + 32) / 2.f;
}

BaseCharacter* GameManager::getBaseCharacter(const std::string& CharName)
{
    if (baseCharacters.find(CharName) != baseCharacters.end())
    {
        return baseCharacters[CharName];
    }
    std::cerr << "GameManager::getBaseCharacter -> BaseCharacter with name " << CharName
              << " not found in baseCharacters map." << std::endl;
    return nullptr;
}

void GameManager::draw()
{
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
    for (auto& pair : baseCharacters)
    {
        pair.second->draw();
    }


    // Draw the lifebars
    lifebar1->Draw();
    lifebar2->Draw();

    // Draw the deadSkull
    deadSkull->drawCurrentSelectedTag(120, 28, 1, WHITE);

#ifdef DEBUG
    // Draw Middlepointline
    DrawLine(middlePointXbetweenPlayers, 0, middlePointXbetweenPlayers, 300, RED);
#endif
}

void GameManager::addInputHandler(InputHandler* inputHandler)
{
    this->inputHandler = inputHandler;
}

InputHandler* GameManager::getInputHandler()
{
    if (inputHandler == nullptr)
    {
        std::cerr << "GameManager::getInputHandler -> InputHandler not set." << std::endl;
    }
    return inputHandler;
}

CollisionManager& GameManager::getCollisionManager()
{
    return collisionManager;
}

void GameManager::addAsepriteManager(AsepriteManager* asepriteManager)
{
    if (asepriteManager == nullptr)
    {
        throw std::runtime_error("AsepriteManager is nullptr");
    }

    this->asepriteManager = asepriteManager;

    // Load the deadSkull animation
    deadSkull = asepriteManager->getAnimFile("deadSkull");
    deadSkull->setFrameTag("deadSkull-Idle");
}

AsepriteManager* GameManager::getAsepriteManager()
{
    this->asepriteManager;
}

void GameManager::setDeltaTimeMultiplier(float deltaTimeMultiplier)
{
    this->deltaTimeMultiplier = deltaTimeMultiplier;
}

void GameManager::playerKo(int playerNumber)
{
    deadSkull->setFrameTag("deadSkull-Amazed");
}
