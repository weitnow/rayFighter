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

void GameObjectsManager::addBaseCharacter(BaseCharacter* character)
{
    baseCharacters.push_back(character);
}

void GameObjectsManager::removeBaseCharacter(BaseCharacter* character)
{
    // Use std::remove to shift all elements not equal to 'character' to the front
    auto newEnd = std::remove(baseCharacters.begin(), baseCharacters.end(), character);

    // Erase the "removed" elements from the vector
    baseCharacters.erase(newEnd, baseCharacters.end());
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
    for (auto character : baseCharacters)
    {
        character->update(deltaTime);
    }

    // Update other game objects
}

void GameObjectsManager::draw()
{
    // Draw all baseCharacters
    for (auto character : baseCharacters)
    {
        character->draw();
    }

    // Draw other game objects
}
