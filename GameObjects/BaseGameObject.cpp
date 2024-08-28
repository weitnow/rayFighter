#include "BaseGameObject.h"
#include "../Constants.h"
#include <assert.h>

BaseGameObject::BaseGameObject(AsepriteManager* asepriteManager)
{
    scale.x = 1.f;
    scale.y = 1.f;
    pos = {Constants::X, Constants::Y};
    this->asepriteManagerPtr = asepriteManager;
    this->animfilePtr = this->asepriteManagerPtr->getAnimFile("gbFighter");
    this->currentFrameTag = "gbFighter-Idle";
    this->animfilePtr->setFrameTag(this->currentFrameTag);
}

BaseGameObject::BaseGameObject(AsepriteManager* asepriteManager, float x, float y) : BaseGameObject(asepriteManager)
{
    setPos(x, y);
}

BaseGameObject::~BaseGameObject()
{
}

void BaseGameObject::update(float deltaTime)
{
    if (scale.x != 1 || scale.y != 1)
    {
        // Todo: Implement scale function
    }

    // update hitboxes
    for (auto& pair : collisionBoxes)
    {
        pair.second.update(deltaTime);
    }

    // check if this->animfileptr is not nullptr - if its not, then update the animation
    if (animfilePtr != nullptr)
    {
        animfilePtr->update(deltaTime);
    }
}

void BaseGameObject::draw()
{
#ifdef DEBUG
    // Draw a small rectangle at the position of the gameobj.
    DrawRectangleLines(pos.x, pos.y, Constants::GAMEOBJ_SIZE.x, Constants::GAMEOBJ_SIZE.y, Constants::GAMEOBJ_COLOR);
#endif
    // Todo: Implement draw function

    // draw this->animfileptr
    if (animfilePtr != nullptr)
    {
        animfilePtr->drawCurrentSelectedTag(getPos().x, getPos().y);
    }
}

void BaseGameObject::setPos(float x, float y)
{
    pos.x = x;
    pos.y = y;
}

void BaseGameObject::setPos(Vector2 pos)
{
    BaseGameObject::setPos(pos.x, pos.y);
}

Vector2 BaseGameObject::getPos()
{
    return pos;
}

void BaseGameObject::setScale(float x, float y)
{
    scale.x = x;
    scale.y = y;
}

void BaseGameObject::setScale(Vector2 scale)
{
    BaseGameObject::setScale(scale.x, scale.y);
}

Vector2 BaseGameObject::getScale()
{
    return scale;
}

void BaseGameObject::addAnim(AsepriteAnimationFile* animfileptr)
{
    this->animfilePtr = animfileptr;
}

AsepriteAnimationFile* BaseGameObject::getAnim()
{
    assert(animfilePtr != nullptr); // ups, getAnim was called before addAnim was called

    return animfilePtr;
}

bool BaseGameObject::setCurrentFrameTag(std::string tag)
{
    // if the animation is already playing, return false, otherwise return true
    // if the tag doesnt exist a runtime-error will be thrown
    bool animAlreadyPlaying = animfilePtr->setFrameTag(tag);
    currentFrameTag = tag;
    return animAlreadyPlaying;
}

std::string BaseGameObject::getCurrentFrameTag()
{
    return currentFrameTag;
}

void BaseGameObject::addCollisionBox(std::string hitboxName)
{
    collisionBoxes[hitboxName] = CollisionBox2D{};
}

void BaseGameObject::removeCollisionBox(std::string hitboxName)
{
    collisionBoxes.erase(hitboxName);
}
