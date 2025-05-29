#include "Fireball.h"

Fireball::Fireball(AsepriteManager* asepriteManagerPtr, float x, float y, bool isFlippedX)
    : BaseGameObject(asepriteManagerPtr, x, y)
{
    this->setObjName("Shot");
    this->setCurrentFrameTag("gbFighter-Shot");
    this->setIsFlippedX(isFlippedX);
    this->setMaxLife(1); // Fireball is destroyed after one hit
    this->setAffectedByGravity(false);
    this->setMoveSpeed(200); // Set a higher speed for the fireball
}

void Fireball::update(float deltaTime)
{
    BaseGameObject::update(deltaTime);

    moveRight();
}
