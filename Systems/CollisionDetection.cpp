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

bool CollisionDetection::checkForCollision(BaseGameObject& gameObject1, BaseGameObject& gameObject2)
{
    return _checkSingleDirectionCollisionInternal(gameObject1, gameObject2) ||
           _checkSingleDirectionCollisionInternal(gameObject2, gameObject1);
}

void CollisionDetection::checkForCollision(vector<unique<BaseGameObject>>& listOfGameObjects1,
                                vector<unique<BaseGameObject>>& listOfGameObjects2)
{
}

bool CollisionDetection::_checkSingleDirectionCollisionInternal(BaseGameObject& attacker, BaseGameObject& defender)
{
    for (auto& hitbox : attacker.getHitBoxes())
    {
        for (auto& hurtbox : defender.getHurtBoxes())
        {
            if (Utils::checkCollision(hitbox, hurtbox) )
            {
                hitboxesThatHit.clear();
                hurtboxesThatWereHit.clear();

                hitboxesThatHit.push_back(&hitbox);
                hurtboxesThatWereHit.push_back(&hurtbox);

                defender.onYouGotHit(hitboxesThatHit, hurtboxesThatWereHit, attacker);
                attacker.onYouHit(hitboxesThatHit, hurtboxesThatWereHit, defender); // here we set also canDealDamage to false
                return true;
            }
        }
    }
    return false;
}

