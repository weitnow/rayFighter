#include "BaseGameObject.h"
#include "../Constants.h"
#include <assert.h>

BaseGameObject::BaseGameObject(AsepriteManager* asepriteManager)
    : ObjName(""), pushVector({0, 0}), scale(1.f), pos{Constants::X, Constants::Y}, color(WHITE), isFlippedX(false),
      isFlippedY(false), isActive(true), isAlive(true), isInvincible(false), life(Constants::DEFAULT_LIFE),
      _invincibleCounter(0.f), invincibleTime(Constants::INVINCIBLE_TIME), affectedByGravity(true), moveVector({0, 0})
{

    this->asepriteManagerPtr = asepriteManager;
    this->animfilePtr = this->asepriteManagerPtr->getAnimFile("gbFighter");
    this->currentFrameTag = "gbFighter-Idle";
    this->animfilePtr->setFrameTag(this->currentFrameTag);
}

BaseGameObject::BaseGameObject(AsepriteManager* asepriteManager, float x, float y) : BaseGameObject(asepriteManager)
{
    setPos(x, y);
    orginalPos = pos; // save the original position for reseting the object
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
        // TODO: Implement scale function
    }

    // update the position
    this->setPos(this->getPos().x + (moveVector.x + pushVector.x) * deltaTime,
                 this->getPos().y + (moveVector.y + pushVector.y) * deltaTime);

    // apply gravity
    if (affectedByGravity)
    {
        _applyGravity(deltaTime);
    }

    // reduce push vector
    _reducePushVector(deltaTime);

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
    if (animfilePtr != nullptr)
    {
#ifdef DEBUG
        if (!isInvincible)
        {
            animfilePtr->drawCurrentSelectedTag(getPos().x, getPos().y, scale, color, isFlippedX, isFlippedY);
        }
        else
        {
            animfilePtr->drawCurrentSelectedTag(getPos().x, getPos().y, scale, BLUE, isFlippedX, isFlippedY);
        }


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

#else
        animfilePtr->drawCurrentSelectedTag(getPos().x, getPos().y, scale, color, isFlippedX, isFlippedY);
#endif
    }
}

void BaseGameObject::takeDamage(float damage)
{
    std::cout << "BaseGameObject::takeDamage -> " << ObjName << " took " << damage << " damage." << std::endl;
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

Vector2 BaseGameObject::getPos() const
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

void BaseGameObject::addCollisionBox(std::string hitboxName,
                                     float offsetX,
                                     float offsetY,
                                     float width,
                                     float height,
                                     CollisionBoxType collisionBoxType,
                                     bool isActive,
                                     Color color)
{
    collisionBoxes[hitboxName] =
        CollisionBox2D{hitboxName, offsetX, offsetY, width, height, collisionBoxType, isActive, color};

    collisionBoxes[hitboxName].setObjPos(
        pos.x,
        pos.y); // set the position of the collision box to the position of the gameobject
}

void BaseGameObject::removeCollisionBox(std::string hitboxName)
{
    collisionBoxes.erase(hitboxName);
}

Dictionary<std::string, CollisionBox2D>& BaseGameObject::getCollisionBoxes()
{
    return collisionBoxes;
}

void BaseGameObject::setPushVector(Vector2 pushVector)
{
    this->pushVector = pushVector;
}

Vector2 BaseGameObject::getPushVector()
{
    return pushVector;
}

void BaseGameObject::resetPushVector()
{
    pushVector = {0, 0};
}

void BaseGameObject::_reducePushVector(float deltaTime)
{
    if (abs(pushVector.x) == 0 && abs(pushVector.y) == 0)
    {
        return;
    }

    // Clamp small pushVector components to zero
    if (abs(pushVector.x) < 5.f)
    {
        pushVector.x = 0;
    }

    if (abs(pushVector.y) < 5.f)
    {
        pushVector.y = 0;
    }

    // Reduce pushVector.x towards zero
    if (pushVector.x > 0.f)
    {
        pushVector.x -= Global::pushReduction * deltaTime;

        // Prevent overshooting below zero
        if (pushVector.x < 0.f)
        {
            pushVector.x = 0.f;
        }
    }
    else if (pushVector.x < 0.f)
    {
        pushVector.x += Global::pushReduction * deltaTime;

        // Prevent overshooting above zero
        if (pushVector.x > 0.f)
        {
            pushVector.x = 0.f;
        }
    }

    // Reduce pushVector.y towards zero
    if (pushVector.y > 0.f)
    {
        pushVector.y -= Global::pushReduction * deltaTime;

        // Prevent overshooting below zero
        if (pushVector.y < 0.f)
        {
            pushVector.y = 0.f;
        }
    }
    else if (pushVector.y < 0.f)
    {
        pushVector.y += Global::pushReduction * deltaTime;

        // Prevent overshooting above zero
        if (pushVector.y > 0.f)
        {
            pushVector.y = 0.f;
        }
    }
}

void BaseGameObject::_applyGravity(float deltaTime)
{
    // apply simplified gravity and check if the object is on its original position
    if (pos.y >= orginalPos.y) // if the object is on the original position or below
    {
        moveVector.y = 0;     // stop falling
        pos.y = orginalPos.y; // set the position to the original position
    }
    else if (pos.y < orginalPos.y) // if the object is above the original position
    {
        moveVector.y += Global::gravity * deltaTime; // apply gravity
    }
}
