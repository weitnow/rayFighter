#include "Fireball.h"

#include "../../Characters/BaseCharacter.h"
#include "../../Characters/Statemachine/Statemachine.h"


Fireball::Fireball(AsepriteManager* asepriteManagerPtr, float x, float y, bool isFlippedX)
    : BaseGameObject(asepriteManagerPtr, x, y)
{
    this->setObjName("Shot");
    this->setCurrentFrameTag("gbFighter-Shot");
    this->setIsFlippedX(isFlippedX);
    this->setMaxLife(1); // Fireball is destroyed after one hit
    this->setAffectedByGravity(false);
    this->setMoveSpeed(120); // Set a higher speed for the fireball
    this->destroyIfHasLeftScreen = true;

    // Add collision boxes for the fireball
    addCollisionBoxForFrame("gbFighter-Shot", -1, CollisionBoxType::HITBOX, true, 10, 14, 10, 8);

    canDealDamage = true; // otherwise hitbox will not register when overlapping with hurtbox
}

void Fireball::update(float deltaTime)
{
    BaseGameObject::update(deltaTime);

    moveRight();
}
void Fireball::handleHitLogic(vector<CollisionBox2D*>& hitboxesThatHit,
                              vector<CollisionBox2D*>& hurtboxesThatWereHit,
                              BaseGameObject& otherGameObject)
{
    otherGameObject.takeDamage(1);
    otherGameObject.setPushVector({120,0});
    if (BaseCharacter* character = dynamic_cast<BaseCharacter*>(&otherGameObject))
    {
        character->getStatemachine().changeState("Hit");
    }

    shouldDestroy = false;
}
