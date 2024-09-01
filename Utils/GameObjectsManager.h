#ifndef GAMEOBJECTSMANAGER_H
#define GAMEOBJECTSMANAGER_H

#include "../Characters/BaseCharacter.h"
#include "../GameObjects/BaseGameObject.h"
#include <algorithm> // for std::remove and std::find

class GameObjectsManager
{
public:
    // Delete copy constructor and assignment operator to prevent copies of the singleton
    GameObjectsManager(const GameObjectsManager&) = delete;
    GameObjectsManager& operator=(const GameObjectsManager&) = delete;

    // Method to access the single instance of the class
    static GameObjectsManager& getInstance();

    // Public methods for managing game objects
    void addBaseCharacter(BaseCharacter* character);
    void removeBaseCharacter(BaseCharacter* character);
    void addObject();
    void removeObject();
    void update(float deltaTime);
    void draw();

private:
    // Private constructor to prevent direct instantiation
    GameObjectsManager();

    // You can add a destructor and any private members or methods here if needed
    ~GameObjectsManager();

    // Private member variables to manage game objects
    std::vector<BaseCharacter*> baseCharacters;
};

#endif //GAMEOBJECTSMANAGER_H
