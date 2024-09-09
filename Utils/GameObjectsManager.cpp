#include "GameObjectsManager.h"

// Define the static method to get the single instance of the class
GameObjectsManager& GameObjectsManager::getInstance()
{
    static GameObjectsManager instance; // This instance will be created the first time this method is called
    return instance;
}

// Private constructor definition
GameObjectsManager::GameObjectsManager()
{
    // Initialize your game objects management here
}

// Optionally, define the destructor
GameObjectsManager::~GameObjectsManager()
{
    // Clean up resources if necessary
}

void GameObjectsManager::addBaseCharacter(const std::string& CharName, BaseCharacter* character)
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

void GameObjectsManager::removeBaseCharacter(const std::string& CharName)
{
    baseCharacters.erase(CharName);
}

// Define the methods to manage game objects
void GameObjectsManager::addObject()
{
    // Implementation of adding an object
}

void GameObjectsManager::removeObject()
{
    // Implementation of removing an object
}

void GameObjectsManager::update(float deltaTime)
{
    // Update all baseCharacters
    for (auto& pair : baseCharacters)
    {
        pair.second->update(deltaTime);
    }

    // Update other game objects
}

BaseCharacter* GameObjectsManager::getBaseCharacter(const std::string& CharName)
{
    if (baseCharacters.find(CharName) != baseCharacters.end())
    {
        return baseCharacters[CharName];
    }
    return nullptr;
}

void GameObjectsManager::draw()
{
    // Draw all baseCharacters
    for (auto& pair : baseCharacters)
    {
        pair.second->draw();
    }

    // Draw other game objects
}
