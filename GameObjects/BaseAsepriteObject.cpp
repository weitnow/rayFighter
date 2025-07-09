//
// Created by weitnow on 7/7/25.
//

#include "BaseAsepriteObject.h"
BaseAsepriteObject::BaseAsepriteObject(AsepriteManager* asepriteManager)
    : BaseSpriteObject(), animfilePtr(nullptr), animFileName(""), currentFrameTag("")
{
    if (!asepriteManager)
    {
        std::cerr << "Error: BaseGameObject received null AsepriteManager!" << std::endl;
        return;
    }
    this->asepriteManagerPtr = asepriteManager;
}
BaseAsepriteObject::BaseAsepriteObject(AsepriteManager* asepriteManager, float x, float y)
    : BaseAsepriteObject(asepriteManager)
{
    setPos(x, y);
}
BaseAsepriteObject::~BaseAsepriteObject()
{
    // free the memory of the animfilePtr
    if (animfilePtr != nullptr)
    {
        delete animfilePtr;
        animfilePtr = nullptr;
    }
}
void BaseAsepriteObject::update(float deltaTime)
{
    if (animfilePtr != nullptr)
    {
        animfilePtr->update(deltaTime);
    }

    BaseSpriteObject::update(deltaTime);
}
void BaseAsepriteObject::draw()
{
    // call Baseclass
    BaseSpriteObject::draw();

    // draw animfilePtr (if it exist)
    if (animfilePtr != nullptr)
    {
        animfilePtr->drawCurrentSelectedTag(getPos().x, getPos().y, scale, WHITE);
    }

}

//setCurrentFrameTag("gbFighter-Idle")
bool BaseAsepriteObject::setCurrentFrameTag(std::string tag)
{
    // if the animation is already playing, return false, otherwise return true
    // if the tag doesnt exist a runtime-error will be thrown

    // check if a animfilePtr is already present
    if (animfilePtr == nullptr)
    {
        // if not, create a new one
        // get first part of tag ("gbFighter-Idle" -> "gbFighter")
        animFileName = tag.substr(0, tag.find("-"));
        // get a animfilePtr
        this->animfilePtr = this->asepriteManagerPtr->getAnimFile(animFileName);
    }

    bool animAlreadyPlaying = animfilePtr->setFrameTag(tag);
    currentFrameTag = tag;
    return animAlreadyPlaying;
}
std::string BaseAsepriteObject::getCurrentFrameTag()
{
    return currentFrameTag;
}
void BaseAsepriteObject::setShouldDestroy(bool shouldDestroy)
{
    this->shouldDestroy = shouldDestroy;
}
bool BaseAsepriteObject::getShouldDestroy()
{
    return shouldDestroy;
}