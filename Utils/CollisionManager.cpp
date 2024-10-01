#include "CollisionManager.h"
#include "GameManager.h"

// Implementation

CollisionManager::CollisionManager(GameManager& manager) : gameManager(manager)
{
}

void CollisionManager::init()
{
    // Get the player objects from the GameManager
    player1 = gameManager.getBaseCharacter("player1");
    player2 = gameManager.getBaseCharacter("player2");
}

void CollisionManager::update(float deltaTime)
{
    // Update positions of all collision boxes // this is done in the update method of the BaseGameObject
    /*
    for (auto box : collisionBoxes)
    {
        box->update(deltaTime);
    }
    */
}

bool CollisionManager::checkCollision(CollisionBox2D& box1, CollisionBox2D& box2)
{
    // Check collision based on their rectangles
    return CheckCollisionRecs(box1.getRectangle(),
                              box2.getRectangle()); // Assuming you are using raylib's CheckCollisionRecs()
}

bool CollisionManager::checkCollision(CollisionBox2D* box1ptr, CollisionBox2D* box2ptr)
{
    // Check collision based on their rectangles
    return CheckCollisionRecs(box1ptr->getRectangle(),
                              box2ptr->getRectangle()); // Assuming you are using raylib's CheckCollisionRecs()
}
