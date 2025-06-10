//
// Created by weitnow on 6/9/25.
//
#include "../Game/GameState.h"
#include "../Characters/BaseCharacter.h"
#include "../Characters/Statemachine/Statemachine.h"
#include "CollisionDetection.h"


CollisionDetection& CollisionDetection::getInstance()
{
    static CollisionDetection instance;
    return instance;
}

CollisionDetection::CollisionDetection() = default;

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

    // check if hitbox of gameObjects1 collides with a hurtbox of gameObjects2
    for (auto& hitbox : gameObject1.getHitBoxes())
    {
        for (auto& hurtbox : gameObject2.getHurtBoxes())
        {
            if (Utils::checkCollision(hitbox, hurtbox) && gameObject1.canDealDamage)
            {
                // clear both lists
                hitboxesThatHit.clear();
                hurtboxesThatWereHit.clear();

                hitboxesThatHit.push_back(&hitbox);
                hurtboxesThatWereHit.push_back(&hurtbox);

                gameObject2.takeDamage(1, &hitbox);
                gameObject2.setPushVector({120, 0});
                gameObject1.canDealDamage = false;

                // Try to cast to BaseCharacter
                if (BaseCharacter* character = dynamic_cast<BaseCharacter*>(&gameObject2))
                {
                    // Transition the opponent into "Hit" or "Hurt" state
                    character->getStatemachine().changeState("Hit");
                }

                gameObject1.onYouHit(hitboxesThatHit, hurtboxesThatWereHit, gameObject2);

                return true; // hit detected
            }
        }
    }
    return false; // no hit detected
}

void CollisionDetection::checkForCollision(BaseGameObject& gameObject, List<unique<BaseGameObject>>& gameObjects) const
{
}
void CollisionDetection::checkForCollision(List<unique<BaseGameObject>>& listOfGameObjects1,
                                List<unique<BaseGameObject>>& listOfGameObjects2) const
{
}