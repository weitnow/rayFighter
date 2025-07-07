//
// Created by weitnow on 7/7/25.
//

#include "BaseAsepriteObject.h"
BaseAsepriteObject::BaseAsepriteObject(AsepriteManager* asepriteManager)
{
    if (!asepriteManager)
    {
        std::cerr << "Error: BaseGameObject received null AsepriteManager!" << std::endl;
        return;
    }
    this->asepriteManagerPtr = asepriteManager;
    this->animfilePtr = this->asepriteManagerPtr->getAnimFile("nesFighter");
    this->currentFrameTag = "nesFighter-Idle";
    this->animfilePtr->setFrameTag(this->currentFrameTag);
}
BaseAsepriteObject::BaseAsepriteObject(AsepriteManager* asepriteManager, float x, float y)
    : BaseAsepriteObject(asepriteManager)
{
    setPos(x, y);
}
BaseAsepriteObject::~BaseAsepriteObject()
{
    // free the memory of the animfilePtr
    delete animfilePtr;
    animfilePtr = nullptr;
}
void BaseAsepriteObject::update(float deltaTime)
{
    if (animfilePtr != nullptr)
    {
        animfilePtr->update(deltaTime);
    }
}
void BaseAsepriteObject::draw()
{
    if (animfilePtr != nullptr)
    {
        animfilePtr->drawCurrentSelectedTag(getPos().x, getPos().y, scale, WHITE);
    }
    else
    {
        std::cerr << "Error: BaseGameObject received null AsepriteAnimationFile!" << std::endl;
    }
}
void BaseAsepriteObject::addAnim(AsepriteAnimationFile* animfileptr)
{
}
AsepriteAnimationFile* BaseAsepriteObject::getAnimFile()
{
}
bool BaseAsepriteObject::setCurrentFrameTag(std::string tag)
{
}
std::string BaseAsepriteObject::getCurrentFrameTag()
{
}
bool BaseAsepriteObject::getShouldDestroy()
{
}