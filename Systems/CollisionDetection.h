//
// Created by weitnow on 6/9/25.
//

#ifndef COLLISIONDETECTION_H
#define COLLISIONDETECTION_H
#include "Core.h"
#include "../GameObjects/BaseGameObject.h"

#include <algorithm>
#include <chrono>


//forward decleration
class GameState;
class BaseGameObject;

class CollisionDetection
{
public:
    static CollisionDetection& getInstance();
    // Delete copy constructor and assignment operator
    CollisionDetection(const CollisionDetection&) = delete;
    CollisionDetection& operator=(const CollisionDetection&) = delete;
    void init(GameState* gameState);
    void update(float deltaTime); // init(GameState* gameState) needed before calling update

    bool checkForCollision(BaseGameObject& gameObject1, BaseGameObject& gameObject2);
    void checkForCollision(BaseGameObject& gameObject, List<unique<BaseGameObject>>& gameObjects) const;
    void checkForCollision(List<unique<BaseGameObject>>& listOfGameObjects1, List<unique<BaseGameObject>>& listOfGameObjects2) const;

private:
    CollisionDetection();
    bool initialized = false;
    GameState* gameState;
    List<CollisionBox2D> hitboxesThatHit;
    List<CollisionBox2D> hurtboxesThatWereHit;
};



#endif //COLLISIONDETECTION_H
