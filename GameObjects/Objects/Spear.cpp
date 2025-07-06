//
// Created by weitnow on 7/5/25.
//

#include "Spear.h"


Spear::Spear(AsepriteManager* asepriteManagerPtr, float x, float y, bool isFlippedX)
    : BaseGameObject(asepriteManagerPtr, x, y)
{
    this->setObjName("Spear");
    this->setCurrentFrameTag("gbSpear-Head");
    this->destroyIfHasLeftScreen = true;
    this->canDealDamage = true;
    this->setMoveSpeed(80);
    addCollisionBoxForFrame("gbSpear-Head", -1, CollisionBoxType::THROWBOX, true, 10, 0, 10, 10);

    if (!isFlippedX)
        movingRight = true;
    else
        movingRight = false;

}


void Spear::update(float deltaTime)
{
    if (movingRight)
        moveRight();
    else
        moveLeft();

    BaseGameObject::update(deltaTime);
}

void Spear::handleHitLogic(vector<CollisionBox2D*>& hitboxesThatHit,
                           vector<CollisionBox2D*>& hurtboxesThatWereHit,
                           BaseGameObject& otherGameObject)
{
    std::cout << "hitbox hit" << '\n';
}
void Spear::handleYouInteractLogic(vector<CollisionBox2D*>& throwBoxThatHit,
                                   vector<CollisionBox2D*>& throwableBoxThatWereHit,
                                   BaseGameObject& otherGameObject)
{
    // on hit switch direction
    std::cout << "youInteractLogic" << '\n';
    movingRight = !movingRight;
}

void Spear::draw()
{
    // draw line
    static int offsety = 5;
    DrawLine(orginalPos.x + offsety, orginalPos.y + offsety, getPos().x + offsety, getPos().y + offsety, BLACK);
    BaseGameObject::draw();
}


