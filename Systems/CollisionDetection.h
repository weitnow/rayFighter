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
    bool hasHitBoxCollision = false;
    bool hasPushBoxCollision = false;
    bool hasThrowBoxCollision = false;
    bool hasProximityBoxCollision = false;
    std::vector<CollisionBox2D*> hitboxesThatHit;
    std::vector<CollisionBox2D*> hurtboxesThatWereHit;
    std::vector<CollisionBox2D*> pushboxesThatWereHit;
    std::vector<CollisionBox2D*> throwboxesThatHit;
    std::vector<CollisionBox2D*> throwableboxesThatWereHit;
    std::vector<CollisionBox2D*> proximityboxesThatHit;
    BaseGameObject* attacker = nullptr;
    BaseGameObject* defender = nullptr;
};


class CollisionDetection : public Singleton<CollisionDetection>
{
    friend class Singleton<CollisionDetection>; // allows access to the private constructor
public:
    std::pair<CollisionResult, CollisionResult> checkForCollision(BaseGameObject& gameObject1, BaseGameObject& gameObject2);

    template <class T1, class T2>
    std::pair<CollisionResult, CollisionResult> checkForCollision(std::vector<std::shared_ptr<T1>>& listOfGameObjects1,
                           std::vector<std::shared_ptr<T2>>& listOfGameObjects2);

    template <typename T>
    std::pair<CollisionResult, CollisionResult> checkForCollision(BaseGameObject& gameObject,
                                                                  std::vector<std::shared_ptr<T>>& gameObjects);
    template <class T1, class T2>
    std::pair<CollisionResult, CollisionResult> checkForCollision(const std::vector<std::weak_ptr<T1>>& weakList1,
                                                                  const std::vector<std::weak_ptr<T2>>& weakList2);
    template <class T>
    std::pair<CollisionResult, CollisionResult> checkForCollision(BaseGameObject& gameObject,
                                                                  const std::vector<std::weak_ptr<T>>& weakGameObjects);

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
        if (result.first.hasHitBoxCollision || result.second.hasHitBoxCollision)
            return result;
    }

    // No collisions or list is empty
    return std::make_pair(CollisionResult(), CollisionResult());
}

template<typename T1, typename T2>
std::pair<CollisionResult, CollisionResult> CollisionDetection::checkForCollision(
    const std::vector<std::weak_ptr<T1>>& weakList1,
    const std::vector<std::weak_ptr<T2>>& weakList2)
{
    auto list1 = lockWeakVector(weakList1);
    auto list2 = lockWeakVector(weakList2);
    return checkForCollision(list1, list2); // reuse shared_ptr version
}

template<typename T>
std::pair<CollisionResult, CollisionResult> CollisionDetection::checkForCollision(
    BaseGameObject& gameObject, const std::vector<std::weak_ptr<T>>& weakGameObjects)
{
    std::vector<std::shared_ptr<T>> sharedGameObjects;
    for (const auto& weakPtr : weakGameObjects)
    {
        if (auto shared = weakPtr.lock())
            sharedGameObjects.push_back(shared);
    }

    return checkForCollision(gameObject, sharedGameObjects); // reuse existing logic
}



#endif //COLLISIONDETECTION_H