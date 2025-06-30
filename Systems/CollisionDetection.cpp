//
// Created by weitnow on 6/9/25.
//
#include "../Game/GameState.h"
#include "../Characters/BaseCharacter.h"
#include "../Characters/Statemachine/Statemachine.h"
#include "CollisionDetection.h"

std::pair<CollisionResult, CollisionResult> CollisionDetection::checkForCollision(BaseGameObject& gameObject1, BaseGameObject& gameObject2)
{
    CollisionResult const result1 = _checkSingleDirectionCollisionInternal(gameObject1, gameObject2);
    CollisionResult const result2 = _checkSingleDirectionCollisionInternal(gameObject2, gameObject1);
    return { result1, result2 };
}

CollisionResult CollisionDetection::_checkSingleDirectionCollisionInternal(BaseGameObject& attacker, BaseGameObject& defender)
{
    CollisionResult result;

    // Hitbox vs Hurtbox (attack)
    for (auto& hitbox : attacker.getHitBoxes())
    {
        for (auto& hurtbox : defender.getHurtBoxes())
        {
            if (Utils::checkCollision(hitbox, hurtbox))
            {
                result.hitboxesThatHit.push_back(&hitbox);
                result.hurtboxesThatWereHit.push_back(&hurtbox);
                result.hasHitBoxCollision = true;

                defender.onYouGotHit(result.hitboxesThatHit, result.hurtboxesThatWereHit, attacker);
                attacker.onYouHit(result.hitboxesThatHit, result.hurtboxesThatWereHit, defender);

                break; // Early return after first successful hit
            }
        }
    }

    // Pushbox vs Pushbox (movement collision)
    for (auto& pushbox1 : attacker.getPushBoxes())
    {
        for (auto& pushbox2 : defender.getPushBoxes())
        {
            if (Utils::checkCollision(pushbox1, pushbox2))
            {
                result.hasPushBoxCollision = true;
                result.pushboxesThatWereHit.push_back(&pushbox2);
                // Todo: Could also call callbacks here if needed
            }
        }
    }

    // Throwbox vs ThrowableBox (throw attempt)
    for (auto& throwbox : attacker.getThrowBoxes())
    {
        for (auto& throwablebox : defender.getThrowableBoxes())
        {
            if (Utils::checkCollision(throwbox, throwablebox))
            {
                result.hasThrowBoxCollision = true;
                result.throwboxesThatHit.push_back(&throwbox);
                result.throwableboxesThatWereHit.push_back(&throwablebox);

                attacker.onYourInteractionBoxHitOther(result.throwboxesThatHit, result.throwableboxesThatWereHit, defender);
            }
        }
    }

    // ProximityBox vs Hurtbox (e.g. for AI awareness)
    for (auto& proximitybox : attacker.getProximityBoxes())
    {
        for (auto& hurtbox : defender.getHurtBoxes())
        {
            if (Utils::checkCollision(proximitybox, hurtbox))
            {
                result.hasProximityBoxCollision = true;
                result.proximityboxesThatHit.push_back(&proximitybox);

                defender.onOtherProximityBoxHitYou(result.proximityboxesThatHit, attacker);

                break; // Early return after first successful hit
            }
        }
    }


    return result;
}

