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
    this->setIsFlippedX(isFlippedX);
    this->setMoveSpeed(30);
    addCollisionBoxForFrame("gbSpear-Head", -1, CollisionBoxType::THROWBOX, true, 10, 0, 10, 10);

}


void Spear::update(float deltaTime)
{
    BaseGameObject::update(deltaTime);

    moveRight();
}

void Spear::handleHitLogic(vector<CollisionBox2D*>& hitboxesThatHit,
                           vector<CollisionBox2D*>& hurtboxesThatWereHit,
                           BaseGameObject& otherGameObject)
{
    std::cout << "hitbox hit" << '\n';
}
void Spear::onYourInteractionBoxHitOther(vector<CollisionBox2D*>& throwBoxThatHit,
                                         vector<CollisionBox2D*>& throwableBoxThatWereHit,
                                         BaseGameObject& otherGameObject)
{
    std::cout << "interactionbox hit" << '\n';
}
void Spear::draw()
{
    // draw line
    static int offsety = 5;
    DrawLine(orginalPos.x + offsety, orginalPos.y + offsety, getPos().x + offsety, getPos().y + offsety, BLACK);
    BaseGameObject::draw();
}


