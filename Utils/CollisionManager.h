#include "../Characters/BaseCharacter.h"
#include "../GameObjects/CollisionBox2D.h"
#include <algorithm> // Include this header for std::remove
#include <iostream>
#include <vector>

#ifndef GBFIGHTER_COLLISIONMANAGER_H
#define GBFIGHTER_COLLISIONMANAGER_H

class GameManager; // Forward declaration of GameManager to avoid circular dependencies

class CollisionManager
{
public:
    // Constructor that takes a reference or pointer to GameManager
    CollisionManager(GameManager& manager);

    // Initialize the collision manager
    void init();

    // Check collisions between all collision boxes
    void update(float deltaTime);

    // Check if two collision boxes collide
    bool checkCollision(CollisionBox2D& box1, CollisionBox2D& box2);
    bool checkCollision(CollisionBox2D* box1ptr, CollisionBox2D* box2ptr);

private:
    GameManager& gameManager; // Reference to the GameManager instance

    BaseCharacter* player1;
    BaseCharacter* player2;
};


#endif //GBFIGHTER_COLLISIONMANAGER_H
