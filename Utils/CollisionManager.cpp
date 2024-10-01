#include "CollisionManager.h"

// Implementation

CollisionManager::CollisionManager(GameManager& manager) : gameManager(manager)
{
}

void CollisionManager::addCollisionBox(CollisionBox2D* box)
{
    collisionBoxes.push_back(box);
}

void CollisionManager::removeCollisionBox(CollisionBox2D* box)
{
    // Find and remove the collision box
    collisionBoxes.erase(std::remove(collisionBoxes.begin(), collisionBoxes.end(), box), collisionBoxes.end());
}

void CollisionManager::update(float deltaTime)
{
    // Update positions of all collision boxes
    for (auto box : collisionBoxes)
    {
        box->update(deltaTime);
    }

    // Check for collisions between all collision boxes
    for (size_t i = 0; i < collisionBoxes.size(); ++i)
    {
        for (size_t j = i + 1; j < collisionBoxes.size(); ++j)
        {
            if (checkCollision(collisionBoxes[i], collisionBoxes[j]))
            {
                // Handle collision (you can define specific collision logic here)
                std::cout << "Collision detected between: " << collisionBoxes[i]->getName() << " and "
                          << collisionBoxes[j]->getName() << std::endl;
            }
        }
    }
}

bool CollisionManager::checkCollision(CollisionBox2D* box1, CollisionBox2D* box2)
{
    // Check collision based on their rectangles
    return CheckCollisionRecs(box1->getRectangle(),
                              box2->getRectangle()); // Assuming you are using raylib's CheckCollisionRecs()
}
