#include "GameManager.h"
#include "CollisionManager.h"

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
GameManager::GameManager() : player1(nullptr), player2(nullptr), player1and2set(false)
{
}

// Optionally, define the destructor
GameManager::~GameManager()
{
    // Clean up resources if necessary
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
    CollisionBox2D& player1PushBox = player1->getCollisionBoxes()["player1PushBox"];
    CollisionBox2D& player2PushBox = player2->getCollisionBoxes()["player2PushBox"];

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

void GameManager::_checkCollisionsBetweenPlayerAndGameObjects()
{


    Dictionary<std::string, CollisionBox2D>& player1CollisionBoxes = player1->getCollisionBoxes();

    // check if there is a key named "punch" in the player1CollisionBoxes

    if (player1CollisionBoxes.find("punch") != player1CollisionBoxes.end())
    {
        // check if the player1 punch hitbox collides with any of the gameObjects
        CollisionBox2D& player1PunchBox = player1CollisionBoxes["punch"];

        for (auto& object : gameObjects)
        {
            Dictionary<std::string, CollisionBox2D>& objectCollisionBoxes = object->getCollisionBoxes();

            for (auto& pair : objectCollisionBoxes)
            {
                CollisionBox2D& objectCollisionBox = pair.second;

                if (collisionManager.checkCollision(player1PunchBox, objectCollisionBox))
                {
                    // Handle collision (you can define specific collision logic here)
                    object->takeDamage();
                }
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
}

void GameManager::update(float deltaTime)
{
    // Set player1 and player2 if not already set
    _setPlayer1and2();

    // Update isLeft for player1 and player2
    _updateIsLeftPlayer1and2();

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

    _checkCollisionsBetweenPlayerAndGameObjects();
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

    // Draw all baseCharacters
    for (auto& pair : baseCharacters)
    {
        pair.second->draw();
    }
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