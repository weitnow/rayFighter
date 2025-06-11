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

class CollisionDetection : public Singleton<CollisionDetection>
{
    friend class Singleton<CollisionDetection>; // allows access to the private constructor
public:

    void init(GameState* gameState);
    void update(float deltaTime); // init(GameState* gameState) needed before calling update

    bool checkForCollision(BaseGameObject& gameObject1, BaseGameObject& gameObject2);
    void checkForCollision(vector<unique<BaseGameObject>>& listOfGameObjects1, vector<unique<BaseGameObject>>& listOfGameObjects2);
    template<typename T>
    void checkForCollision(BaseGameObject& gameObject, vector<unique<T>>& gameObjects);

private:
    CollisionDetection() = default ; // private constructor, because singleton
    bool _checkSingleDirectionCollisionInternal(BaseGameObject& attacker, BaseGameObject& defender);
    bool initialized = false;
    GameState* gameState;
    vector<CollisionBox2D*> hitboxesThatHit;
    vector<CollisionBox2D*> hurtboxesThatWereHit;
};

template<typename T>
void CollisionDetection::checkForCollision(BaseGameObject& gameObject, vector<unique<T>>& gameObjects)
{
    for (auto& otherGameObject : gameObjects)
    {
        if (otherGameObject) {
            checkForCollision(gameObject, *otherGameObject.get());
        } else
        {
            throw std::runtime_error("Null game object encountered in collision detection");
        }
    }
}


#endif //COLLISIONDETECTION_H