#include "BaseCharacter.h"
#include "../Constants.h"
#include "Statemachine/Statemachine.h"

BaseCharacter::BaseCharacter(AsepriteManager* asepriteManager, float x, float y)
    : BaseGameObject(asepriteManager, x, y), moveDirection({0, 0}), jumpForce(4.4f), walkingSpeed(1.f),
      isOnGround(false), animFileName("gbFighter"), isLeft(true), playerNumber(-1),
      statemachine(std::make_unique<Statemachine>(*this)), currentState("Idle")
{
    statemachine->setOwner(this);
}


BaseCharacter::~BaseCharacter()
{
}

void BaseCharacter::update(float deltaTime)
{
    if (scale != 1)
    {
        // TODO: Implement scale function
    }

    this->setPos(this->getPos().x + moveDirection.x, this->getPos().y);

    if (this->getPos().x < 0)
    {
        this->setPos(0, this->getPos().y);
    }
    else if (this->getPos().x > 258 - 32) // TODO: get rid of hardcoded values
    {
        this->setPos(258 - 32, this->getPos().y); // TODO: get rid of hardcoded values
    }

    this->setPos(this->getPos().x, this->getPos().y + moveDirection.y);

    //apply gravity
    //if character is on the ground, stop falling
    if (this->getPos().y > Constants::BASELINE || isOnGround)
    {
        this->isOnGround = true;
        this->setPos(this->getPos().x, Constants::BASELINE);
        this->moveDirection.y = 0;
    }
    else if (this->getPos().y < Constants::BASELINE || !isOnGround)
    {
        this->moveDirection.y += Global::gravity * deltaTime;
    }

    // update hitboxes
    for (auto& pair : collisionBoxes)
    {
        pair.second.update(deltaTime);
        pair.second.setObjPos(getPos().x, getPos().y);
    }

    //TODO: get rid of the follow code - just testing
    if (std::abs(moveDirection.x) > 0 && isOnGround)
    {
        statemachine->changeState("Walk");
    }
    if (std::abs(moveDirection.x) < 0.1f && isOnGround)
    {
        statemachine->changeState("Idle");
    }
    if (!isOnGround)
    {
        statemachine->changeState("Jump");
    }


    // update the state
    statemachine->update(deltaTime);


    // update the sprite
    if (currentState != statemachine->getCurrentStateAsString())
    {
        currentState = statemachine->getCurrentStateAsString();
        setCurrentFrameTag(animFileName + "-" + statemachine->getCurrentStateAsString());
    }


    // check if this->animfileptr is not nullptr - if its not, then update the animation
    if (animfilePtr != nullptr)
    {
        animfilePtr->update(deltaTime);
    }
}


void BaseCharacter::draw()
{

    BaseGameObject::draw();
}

void BaseCharacter::moveLeft()
{

    this->moveDirection.x = -walkingSpeed;
}

void BaseCharacter::moveRight()
{

    this->moveDirection.x = +walkingSpeed;
}

void BaseCharacter::stop()
{
    this->moveDirection.x = 0;
}

void BaseCharacter::jump()
{
    if (this->isOnGround)
    {
        this->moveDirection.y = -jumpForce;
        this->isOnGround = false;
    }
}

void BaseCharacter::duck()
{
}

void BaseCharacter::punch()
{
}

void BaseCharacter::setIsLeft(bool isLeft)
{
    this->isLeft = isLeft;
    // if the character is left, flip the sprite
    // TODO: refactor this methode
    if (isLeft)
    {
        this->isFlippedX = false;
    }
    else
    {
        this->isFlippedX = true;
    }
}

bool BaseCharacter::getIsLeft()
{
    return isLeft;
}

void BaseCharacter::setPlayerNumber(int playerNumber)
{
    if (playerNumber != 1 && playerNumber != 2)
    {
        throw std::invalid_argument("Player number must be 1 or 2");
    }

    // check if the player has a ObjName
    if (this->getObjName().empty())
    {
        this->setObjName("Player" + std::to_string(playerNumber));
    }
    this->playerNumber = playerNumber;
}

int BaseCharacter::getPlayerNumber()
{
    return playerNumber;
}

bool BaseCharacter::setCurrentFrameTag(std::string tag)
{
    // set animFilename to the first part of the tag for example "gbFighter-Idle" -> "gbFighter"
    animFileName = tag.substr(0, tag.find("-"));
    // this is needed to set the correct animation when changing states by calling changeState()

    // if the animation is already playing, return false, otherwise return true
    return BaseGameObject::setCurrentFrameTag(tag);
}


std::string BaseCharacter::getCurrentState()
{
    return currentState;
}

bool BaseCharacter::getIsOnGround()
{
    return isOnGround;
}

Vector2 BaseCharacter::getMoveDirection()
{
    return moveDirection;
}
