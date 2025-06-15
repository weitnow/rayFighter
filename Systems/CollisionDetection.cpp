//
// Created by weitnow on 6/9/25.
//
#include "../Game/GameState.h"
#include "../Characters/BaseCharacter.h"
#include "../Characters/Statemachine/Statemachine.h"
#include "CollisionDetection.h"


void CollisionDetection::init(GameState* gameState)
{
    if (!initialized)
    {
        initialized = true;

        // reference gamestate
        this->gameState = gameState;
    }
}
void CollisionDetection::update(float deltaTime)
{
    if (!initialized)
    {
        std::cerr << "hit detection ist not initialized!" << std::endl;
        return;
    }

}



std::pair<CollisionResult, CollisionResult> CollisionDetection::checkForCollision(BaseGameObject& gameObject1, BaseGameObject& gameObject2)
{
    CollisionResult const result1 = _checkSingleDirectionCollisionInternal(gameObject1, gameObject2);
    CollisionResult const result2 = _checkSingleDirectionCollisionInternal(gameObject2, gameObject1);
    return { result1, result2 };
}

CollisionResult CollisionDetection::_checkSingleDirectionCollisionInternal(BaseGameObject& attacker, BaseGameObject& defender)
{
    CollisionResult result;

    for (auto& hitbox : attacker.getHitBoxes())
    {
        for (auto& hurtbox : defender.getHurtBoxes())
        {
            if (Utils::checkCollision(hitbox, hurtbox))
            {
                result.hitboxesThatHit.push_back(&hitbox);
                result.hurtboxesThatWereHit.push_back(&hurtbox);
                result.hasCollision = true;

                defender.onYouGotHit(result.hitboxesThatHit, result.hurtboxesThatWereHit, attacker);
                attacker.onYouHit(result.hitboxesThatHit, result.hurtboxesThatWereHit, defender);

                return result; // early return after first hit
            }
        }
    }

    return result;
}

