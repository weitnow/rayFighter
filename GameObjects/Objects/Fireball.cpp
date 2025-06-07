#include "Fireball.h"

Fireball::Fireball(AsepriteManager* asepriteManagerPtr, float x, float y, bool isFlippedX)
    : BaseGameObject(asepriteManagerPtr, x, y)
{
    this->setObjName("Shot");
    this->setCurrentFrameTag("gbFighter-Shot");
    this->setIsFlippedX(isFlippedX);
    this->setMaxLife(1); // Fireball is destroyed after one hit
    this->setAffectedByGravity(false);
    this->setMoveSpeed(10); // Set a higher speed for the fireball

    // Add collision boxes for the fireball
    addCollisionBoxForFrame("gbFighter-Shot", -1, CollisionBoxType::HITBOX, true, 10, 14, 10, 8);
}

void Fireball::update(float deltaTime)
{
    BaseGameObject::update(deltaTime);

    moveRight();
}
