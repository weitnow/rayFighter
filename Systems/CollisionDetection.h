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

struct CollisionResult
{
    bool hasCollision = false;
    std::vector<CollisionBox2D*> hitboxesThatHit;
    std::vector<CollisionBox2D*> hurtboxesThatWereHit;
};


class CollisionDetection : public Singleton<CollisionDetection>
{
    friend class Singleton<CollisionDetection>; // allows access to the private constructor
public:

    void init(GameState* gameState);
    void update(float deltaTime); // init(GameState* gameState) needed before calling update

    std::pair<CollisionResult, CollisionResult> checkForCollision(BaseGameObject& gameObject1, BaseGameObject& gameObject2);

    template <class T1, class T2>
    std::pair<CollisionResult, CollisionResult>  checkForCollision(std::vector<std::shared_ptr<T1>>& listOfGameObjects1,
                           std::vector<std::shared_ptr<T2>>& listOfGameObjects2);

    template <typename T>
    std::pair<CollisionResult, CollisionResult>  checkForCollision(BaseGameObject& gameObject, std::vector<std::shared_ptr<T>>& gameObjects);

private:
    CollisionDetection() = default ; // private constructor, because singleton
    CollisionResult _checkSingleDirectionCollisionInternal(BaseGameObject& attacker, BaseGameObject& defender);
    bool initialized = false;
    GameState* gameState;
    vector<CollisionBox2D*> hitboxesThatHit;
    vector<CollisionBox2D*> hurtboxesThatWereHit;
};

template<typename T1, typename T2>
std::pair<CollisionResult, CollisionResult> CollisionDetection::checkForCollision(
    std::vector<std::shared_ptr<T1>>& listOfGameObjects1,
    std::vector<std::shared_ptr<T2>>& listOfGameObjects2)
{
    for (auto& gameObject1 : listOfGameObjects1)
    {
        if (!gameObject1) continue;

        for (auto& gameObject2 : listOfGameObjects2)
        {
            if (!gameObject2) continue;

            auto result = checkForCollision(*gameObject1, *gameObject2);
            if (result.first.hasCollision || result.second.hasCollision)
                return result;
        }
    }

    // No collisions or lists empty
    return std::make_pair(CollisionResult(), CollisionResult());
}


template<typename T>
std::pair<CollisionResult, CollisionResult> CollisionDetection::checkForCollision(
    BaseGameObject& gameObject, std::vector<std::shared_ptr<T>>& gameObjects)
{
    for (auto& otherGameObject : gameObjects)
    {
        if (!otherGameObject)
            continue;

        auto result = checkForCollision(gameObject, *otherGameObject);
        if (result.first.hasCollision || result.second.hasCollision)
            return result;
    }

    // No collisions or list is empty
    return std::make_pair(CollisionResult(), CollisionResult());
}


#endif //COLLISIONDETECTION_H