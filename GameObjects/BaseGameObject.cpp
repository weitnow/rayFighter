#include "BaseGameObject.h"
#include "../Constants.h"
#include <assert.h>

BaseGameObject::BaseGameObject(AsepriteManager* asepriteManager)
    : ObjName(""), pushVector({0, 0}), scale(1.f), pos{0.f, 0.f}, color(WHITE), isFlippedX(false), isFlippedY(false),
      isActive(true), isAlive(true), isInvincible(false), maxLife(1), currentLife(maxLife), _invincibleCounter(0.f),
      invincibleTime(Constants::INVINCIBLE_TIME), affectedByGravity(false), moveVector({0, 0}),
      getDurationCurrentFrame(0), currentFrame(0), minFrame(0), maxFrame(0), hasAnimJustFinished(false),
      currentFrameTag(""), currentFrameAbsolut(0), drawShadow(false)
{
    if (!asepriteManager)
    {
        std::cerr << "Error: BaseGameObject received null AsepriteManager!" << std::endl;
        return;
    }
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

void BaseGameObject::init()
{
}

void BaseGameObject::update(float deltaTime)
{
    if (scale != 1)
    {
        // TODO: Implement scale function
    }

    // update collision boxes
    _updateCollisionBoxes(deltaTime);

    this->setPos(this->getPos().x + (moveVector.x + pushVector.x) * deltaTime,
                 this->getPos().y + (moveVector.y + pushVector.y) * deltaTime);


    // apply gravity
    if (affectedByGravity)
    {
        _applyGravity(deltaTime);
    }

    // reduce push vector
    _reducePushVector(deltaTime);

    // update the member variables from the animationfile
    _updateMemberVariables();

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

        // Draw the shadow
        if (drawShadow)
        {
            _drawShadow(shadowGroundLevel, shadowSize, shadowColor, shadowOpacity);
        }

        if (Global::debugMode)
        {
            if (!isInvincible)
            {
                animfilePtr->drawCurrentSelectedTag(getPos().x, getPos().y, scale, color, isFlippedX, isFlippedY);
            }
            else //if the object is invincible draw it in blue
            {
                animfilePtr->drawCurrentSelectedTag(getPos().x, getPos().y, scale, BLUE, isFlippedX, isFlippedY);
            }


            // Draw a small rectangle at the position of the gameobj.

            DrawRectangleLines(getPos().x,
                               getPos().y,
                               Constants::GAMEOBJ_SIZE.x,
                               Constants::GAMEOBJ_SIZE.y,
                               Constants::GAMEOBJ_COLOR);


            // Draw the Spriteborder
            if (Global::debugSpriteBorder)
            {
                DrawRectangleLines(getPos().x,
                                   getPos().y,
                                   animfilePtr->getSpriteSizeX() * scale,
                                   animfilePtr->getSpriteSizeY() * scale,
                                   YELLOW);
            }
            if (Global::debugCollisionBoxes)
            {
                // Draw the collision boxes
                _drawCollisionBoxes();
            }
        }
        else
        {

            animfilePtr->drawCurrentSelectedTag(getPos().x, getPos().y, scale, color, isFlippedX, isFlippedY);
        }
    }
}

void BaseGameObject::takeDamage(float damage)
{

    currentLife -= damage;

    if (currentLife <= 0)
    {
        currentLife = 0;
        isAlive = false;
    }
}

void BaseGameObject::takeDamage(float damage, CollisionBox2D* hitbox)
{
    std::cout << "BaseGameObject::takeDamage -> " << ObjName << " took " << damage << " damage." << std::endl;

    takeDamage(damage);
}


int BaseGameObject::getMaxLife() // use only for initialization
{
    return maxLife;
}

void BaseGameObject::setMaxLife(int maxLife) // use only for initialization
{
    this->maxLife = maxLife;
    this->setCurrentLife(maxLife);
}

int BaseGameObject::getCurrentLife()
{
    return currentLife;
}

bool BaseGameObject::getIsAlive()
{
    return isAlive;
}

bool BaseGameObject::getIsActive()
{
    return isActive;
}

void BaseGameObject::setCurrentLife(int currentLife)
{
    this->currentLife = currentLife;
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

void BaseGameObject::resetPos()
{

    pos = orginalPos;
}

void BaseGameObject::setAffectedByGravity(bool affectedByGravity)
{
    this->affectedByGravity = affectedByGravity;
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

void BaseGameObject::setDrawShadow(bool drawShadow)
{
    this->drawShadow = drawShadow;
}

void BaseGameObject::setShadowGroundLevel(int groundlevel)
{
    shadowGroundLevel = groundlevel;
}

void BaseGameObject::setShadowSize(float size)
{
    shadowSize = size;
}

void BaseGameObject::setShadowColor(Color color)
{
    shadowColor = color;
}

void BaseGameObject::setShadowOpacity(float opacity)
{
    shadowOpacity = opacity;
}

void BaseGameObject::setIsFlippedX(bool isFlippedX)
{
    this->isFlippedX = isFlippedX;
}

bool BaseGameObject::getIsFlippedX()
{
    return isFlippedX;
}

// TODO: refactor this method to return a reference to the list and not a copy
List<CollisionBox2D> BaseGameObject::getPushBoxes()
{
    return _checkIfCollisionMapHasCollisionBoxesAndReturnList(currentFrameTag,
                                                              currentFrameAbsolut,
                                                              CollisionBoxType::PUSHBOX);
}

List<CollisionBox2D> BaseGameObject::getHitBoxes()
{
    return _checkIfCollisionMapHasCollisionBoxesAndReturnList(currentFrameTag,
                                                              currentFrameAbsolut,
                                                              CollisionBoxType::HITBOX);
}

List<CollisionBox2D> BaseGameObject::getHurtBoxes()
{
    return _checkIfCollisionMapHasCollisionBoxesAndReturnList(currentFrameTag,
                                                              currentFrameAbsolut,
                                                              CollisionBoxType::HURTBOX);
}

List<CollisionBox2D> BaseGameObject::getThrowBoxes()
{
    return _checkIfCollisionMapHasCollisionBoxesAndReturnList(currentFrameTag,
                                                              currentFrameAbsolut,
                                                              CollisionBoxType::THROWBOX);
}

void BaseGameObject::addCollisionBoxForFrame(const std::string frameTag,
                                             int frameNumber,
                                             CollisionBoxType collisionBoxType,
                                             HurtboxType hurtboxType,
                                             bool isActive,
                                             float offsetX,
                                             float offsetY,
                                             float width,
                                             float height)
{
    std::string frameTagName = frameTag;

    if (frameNumber == -1)
    {
        // the collision box is valid for all frames
        // frameTag ex "gbFighter-Idle"
        // get rid of the -Idle part
        // and set the frameTagName to "gbFighter"
        frameTagName = frameTag.substr(0, frameTag.find("-"));
    }
    else if (frameNumber == -2)
    {
        // the collision box is valid all frames of the frameTagName
        // get the min and max frame number of the frameTagName
        FrameTag tag = asepriteManagerPtr->getFrameTag(frameTag);
        int NumberOfFrames = tag.to - tag.from;

        for (int i = 0; i <= NumberOfFrames; ++i)
        {
            frameTagName = frameTag + std::to_string(i);
            _addCollisionBoxForFrameInternal(frameTagName,
                                             offsetX,
                                             offsetY,
                                             width,
                                             height,
                                             tag.sourceSizeX,
                                             collisionBoxType,
                                             hurtboxType,
                                             isActive);
        }
        return;
    }
    else
    {
        // the collision box is valid for a specific frame ex. "gbFighter-Idle0"
        frameTagName += std::to_string(frameNumber);
    }

    // get the with of the sprite from the frametag
    int sourceSizeX = asepriteManagerPtr->getFrameTag(frameTag).sourceSizeX;


    _addCollisionBoxForFrameInternal(frameTagName,
                                     offsetX,
                                     offsetY,
                                     width,
                                     height,
                                     sourceSizeX,
                                     collisionBoxType,
                                     hurtboxType,
                                     isActive);
}

void BaseGameObject::addCollisionBoxForFrame(const std::string frameTag,
                                             int frameNumber,
                                             CollisionBoxType collisionBoxType,
                                             bool isActive,
                                             float offsetX,
                                             float offsetY,
                                             float width,
                                             float height)
{
#ifdef DEBUG
    if (collisionBoxType == CollisionBoxType::HURTBOX)
    {
        std::cerr << "BaseGameObject::addCollisionBoxForFrame -> "
                  << "You have to specify a HurtboxType for a Hurtbox. "
                  << "Otherwise HurtboxType::BODY assumed" << std::endl;
    }
#endif


    addCollisionBoxForFrame(frameTag,
                            frameNumber,
                            collisionBoxType,
                            HurtboxType::BODY,
                            isActive,
                            offsetX,
                            offsetY,
                            width,
                            height);
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

void BaseGameObject::setMoveVector(Vector2 moveVector)
{
    this->moveVector = moveVector;
}

void BaseGameObject::setMoveVectorY(int yValue)
{
    moveVector.y = yValue;
}

void BaseGameObject::setMoveVectorX(int xValue)
{
    moveVector.x = xValue;
}

void BaseGameObject::moveLeft()
{
    this->moveVector.x = -moveSpeed;
}

void BaseGameObject::moveRight()
{
    this->moveVector.x = +moveSpeed;
}

void BaseGameObject::moveUp()
{
    this->moveVector.y = -moveSpeed;
}

void BaseGameObject::moveDown()
{
    this->moveVector.y = +moveSpeed;
}

void BaseGameObject::stop()
{
    this->moveVector.x = 0;
}

void BaseGameObject::setMoveSpeed(int speed)
{
    moveSpeed = speed;
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

void BaseGameObject::_updateCollisionBoxes(float deltaTime)
{
    // List of all your CollisionMaps
    List<CollisionMap*> collisionMaps = {&hitBoxesPerFrame,
                                         &hurtBoxesPerFrame,
                                         &pushBoxesPerFrame,
                                         &throwBoxesPerFrame};

    // Loop through each CollisionMap
    for (auto* collisionMap : collisionMaps)
    {
        // Loop through each frameTag (key = string, value = List<CollisionBox2D>)
        for (auto& tagPair : *collisionMap)
        {
            const std::string& frameTag = tagPair.first;
            auto& collisionBoxList = tagPair.second;

            // Loop through each CollisionBox2D object and call its update method
            for (auto& collisionBox : collisionBoxList)
            {
                collisionBox.setObjPos(pos.x, pos.y);
                collisionBox.update(deltaTime, isFlippedX);
            }
        }
    }
}

void BaseGameObject::_drawCollisionBoxes()
{
    // Draw the Hitboxes for the current frame
    if (Global::debugHitboxes)
    {
        List<CollisionBox2D> collisionBoxes =
            _checkIfCollisionMapHasCollisionBoxesAndReturnList(currentFrameTag,
                                                               currentFrameAbsolut,
                                                               CollisionBoxType::HITBOX);
        for (auto& box : collisionBoxes)
        {
            box.draw();
        }
    }


    // Draw the Hurtboxes for the current frame
    if (Global::debugHurtboxes)
    {
        List<CollisionBox2D> collisionBoxes =
            _checkIfCollisionMapHasCollisionBoxesAndReturnList(currentFrameTag,
                                                               currentFrameAbsolut,
                                                               CollisionBoxType::HURTBOX);
        for (auto& box : collisionBoxes)
        {
            box.draw();
        }
    }


    // Draw the Pushboxes for the current frame
    if (Global::debugPushboxes)
    {
        List<CollisionBox2D> collisionBoxes =
            _checkIfCollisionMapHasCollisionBoxesAndReturnList(currentFrameTag,
                                                               currentFrameAbsolut,
                                                               CollisionBoxType::PUSHBOX);
        for (auto& box : collisionBoxes)
        {
            box.draw();
        }
    }


    // Draw the Throwboxes for the current frame
    if (Global::debugThrowboxes)
    {
        List<CollisionBox2D> collisionBoxes =
            _checkIfCollisionMapHasCollisionBoxesAndReturnList(currentFrameTag,
                                                               currentFrameAbsolut,
                                                               CollisionBoxType::THROWBOX);
        for (auto& box : collisionBoxes)
        {
            box.draw();
        }
    }
}

void BaseGameObject::_addCollisionBoxForFrameInternal(std::string frameTagName,
                                                      int offsetX,
                                                      int offsetY,
                                                      int width,
                                                      int height,
                                                      float hitboxOwnerWith,
                                                      CollisionBoxType collisionBoxType,
                                                      HurtboxType hurtboxType,
                                                      bool isActive)
{
    if (collisionBoxType == CollisionBoxType::HITBOX)
    {
        hitBoxesPerFrame[frameTagName].push_back(CollisionBox2D{offsetX,
                                                                offsetY,
                                                                width,
                                                                height,
                                                                hitboxOwnerWith,
                                                                collisionBoxType,
                                                                isActive,
                                                                RED,
                                                                hurtboxType});
    }
    else if (collisionBoxType == CollisionBoxType::HURTBOX)
    {
        hurtBoxesPerFrame[frameTagName].push_back(CollisionBox2D{offsetX,
                                                                 offsetY,
                                                                 width,
                                                                 height,
                                                                 hitboxOwnerWith,
                                                                 collisionBoxType,
                                                                 isActive,
                                                                 GREEN,
                                                                 hurtboxType});
    }
    else if (collisionBoxType == CollisionBoxType::PUSHBOX)
    {
        pushBoxesPerFrame[frameTagName].push_back(CollisionBox2D{offsetX,
                                                                 offsetY,
                                                                 width,
                                                                 height,
                                                                 hitboxOwnerWith,
                                                                 collisionBoxType,
                                                                 isActive,
                                                                 BLUE,
                                                                 hurtboxType});
    }
    else if (collisionBoxType == CollisionBoxType::THROWBOX)
    {
        throwBoxesPerFrame[frameTagName].push_back(CollisionBox2D{offsetX,
                                                                  offsetY,
                                                                  width,
                                                                  height,
                                                                  hitboxOwnerWith,
                                                                  collisionBoxType,
                                                                  isActive,
                                                                  BROWN,
                                                                  hurtboxType});
    }
    else
    {
        throw std::runtime_error("CollisionBoxType not found");
    }
}

void BaseGameObject::_updateMemberVariables()
{
    // update member variables of the gameobject from the animationfile
    getDurationCurrentFrame = animfilePtr->getDurationCurrentFrame();
    currentFrame = animfilePtr->getCurrentFrame();
    minFrame = animfilePtr->getMinFrame();
    maxFrame = animfilePtr->getMaxFrame();
    hasAnimJustFinished = animfilePtr->hasAnimJustFinished();
    currentFrameAbsolut = currentFrame - minFrame;
}

void BaseGameObject::_drawShadow(int groundLevel, float shadowSize, Color color, float shadowOpacity)
{
    const float x1 = 97, y1 = 1.0f;
    const float x2 = 40, y2 = 0.7f;

    float shadowSizeAdjustment = y1 + ((pos.y - x1) * (y2 - y1)) / (x2 - x1);

    DrawEllipse(pos.x + 16,
                groundLevel,
                13 * shadowSizeAdjustment * shadowSize,
                7 * shadowSizeAdjustment * shadowSize,
                Fade(color, shadowOpacity));
}

List<CollisionBox2D> BaseGameObject::_checkIfCollisionMapHasCollisionBoxesAndReturnList(
    const std::string& currentFrameTag,
    const int currentFrameAbsolut,
    CollisionBoxType collisionBoxType)
{
    //Reference to the appropriate CollisionMap
    CollisionMap* collisionMap = nullptr;

    // Get rid of the -Idle part
    std::string currentFrameTagWithoutIdle = currentFrameTag.substr(0, currentFrameTag.find("-"));

    // Determine which CollisionMap to use based on collisionBoxType
    switch (collisionBoxType)
    {
    case CollisionBoxType::HITBOX:
        collisionMap = &hitBoxesPerFrame;
        break;
    case CollisionBoxType::HURTBOX:
        collisionMap = &hurtBoxesPerFrame;
        break;
    case CollisionBoxType::PUSHBOX:
        collisionMap = &pushBoxesPerFrame;
        break;
    case CollisionBoxType::THROWBOX:
        collisionMap = &throwBoxesPerFrame;
        break;
    default:
        throw std::runtime_error("Invalid CollisionBoxType");
    }

    // Create an empty vector of CollisionBox2D
    List<CollisionBox2D> collisionBoxes;

    // Check if the currentFrameTag exists in the chosen collisionMap
    auto tagIt = collisionMap->find(currentFrameTag + std::to_string(currentFrameAbsolut));
    if (tagIt != collisionMap->end())
    {
        // if the tag exists, return the vector of CollisionBox for the existing tag and frame
        collisionBoxes.insert(collisionBoxes.end(), tagIt->second.begin(), tagIt->second.end());
    }
    // Check if the currentFrameTag exists in the chosen collisionMap without the frame number and without the -Idle
    if (collisionMap->find(currentFrameTagWithoutIdle) != collisionMap->end())
    {
        // if the tag exists, return the vector of CollisionBox for the existing tag and frame
        collisionBoxes.insert(collisionBoxes.end(),
                              collisionMap->at(currentFrameTagWithoutIdle).begin(),
                              collisionMap->at(currentFrameTagWithoutIdle).end());
    }

    // return an empty vector if the frame does not exist
    return collisionBoxes;
}
