#include "BaseGameObject.h"
#include "../Constants.h"
#include <assert.h>

BaseGameObject::BaseGameObject(AsepriteManager* asepriteManager) : ObjName("")
{
    scale = 1.f;
    pos = {Constants::X, Constants::Y};
    color = WHITE;
    isFlippedX = false;
    isFlippedY = false;
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
    // free the memory of the animfilePtr
    delete animfilePtr;
    animfilePtr = nullptr;
}

void BaseGameObject::update(float deltaTime)
{
    if (scale != 1)
    {
        // Todo: Implement scale function
    }

    // update hitboxes
    for (auto& pair : collisionBoxes)
    {
        pair.second.update(deltaTime);
        pair.second.setObjPos(pos.x, pos.y);
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
    DrawRectangleLines(getPos().x,
                       getPos().y,
                       Constants::GAMEOBJ_SIZE.x,
                       Constants::GAMEOBJ_SIZE.y,
                       Constants::GAMEOBJ_COLOR);

    // Draw collision boxes
    for (auto& pair : collisionBoxes)
    {
        pair.second.draw();
    }
#endif

    if (animfilePtr != nullptr)
    {
        animfilePtr->drawCurrentSelectedTag(getPos().x, getPos().y, scale, color, isFlippedX, isFlippedY);
    }
}

void BaseGameObject::setObjName(std::string name)
{
    ObjName = name;
}

std::string BaseGameObject::getObjName()
{
    return ObjName;
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

void BaseGameObject::setScale(float scale)
{
    this->scale = scale;
}

float BaseGameObject::getScale()
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

void BaseGameObject::addCollisionBox(std::string hitboxName, float x, float y, float width, float height, Color color)
{
    collisionBoxes[hitboxName] = CollisionBox2D{hitboxName, x, y, width, height, color};
}

void BaseGameObject::removeCollisionBox(std::string hitboxName)
{
    collisionBoxes.erase(hitboxName);
}
