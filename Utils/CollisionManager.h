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

    // Add a new collision box to the manager
    void addCollisionBox(CollisionBox2D* box);

    // Remove a collision box from the manager
    void removeCollisionBox(CollisionBox2D* box);

    // Check collisions between all collision boxes
    void update(float deltaTime);

private:
    // Vector storing all the collision boxes
    std::vector<CollisionBox2D*> collisionBoxes;

    // Check if two collision boxes collide
    bool checkCollision(CollisionBox2D* box1, CollisionBox2D* box2);

    GameManager& gameManager; // Reference to the GameManager instance
};


#endif //GBFIGHTER_COLLISIONMANAGER_H
