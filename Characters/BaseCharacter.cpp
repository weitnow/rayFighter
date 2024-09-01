//
// Created by weitnow on 12/7/23.
//

#include "BaseCharacter.h"
#include "../Constants.h"


std::string CharacterStateToString(CharacterState state)
{
    switch (state)
    {
    case CharacterState::Idle:
        return "Idle";
    case CharacterState::Walk:
        return "Walk";
    case CharacterState::Jump:
        return "Jump";
    case CharacterState::Duck:
        return "Duck";
    case CharacterState::Punch:
        return "Punch";
    case CharacterState::Kick:
        return "Kick";
    case CharacterState::Block:
        return "Block";
    case CharacterState::Hit:
        return "Hit";
    case CharacterState::Hurt:
        return "Hurt";
    default:
        return "Unknown State";
    }
}


void BaseCharacter::changeState(CharacterState newState)
{
    if (currentState != newState) // if the new state is different from the current state
    {
#ifdef DEBUG_CHANGE_STATE
        std::cout << "Changing state from " << getCurrentState() << " to " << CharacterStateToString(newState)
                  << std::endl;
#endif

        currentState = newState;
        if (currentState == CharacterState::Idle)
        {
            setCurrentFrameTag(animFileName + "-Idle");
        }
        else if (currentState == CharacterState::Walk)
        {
            setCurrentFrameTag(animFileName + "-Walking");
        }
        else if (currentState == CharacterState::Jump)
        {
            setCurrentFrameTag(animFileName + "-Jump");
        }
    }
}

void BaseCharacter::updateState()
{
    if (std::abs(moveDirection.x) > 0 && isOnGround)
    {
        changeState(CharacterState::Walk);
    }
    else if (std::abs(moveDirection.x) < 0.1 && isOnGround)
    {
        changeState(CharacterState::Idle);
    }
    else if (!isOnGround)
    {
        changeState(CharacterState::Jump);
    }
    else
    {
        /* code */
    }
}

BaseCharacter::BaseCharacter(AsepriteManager* asepriteManager) : BaseGameObject(asepriteManager)
{
}

BaseCharacter::BaseCharacter(AsepriteManager* asepriteManager, float x, float y)
    : BaseGameObject(asepriteManager, x, y), currentState(CharacterState::Idle), moveDirection({0, 0}), jumpForce(4.4f),
      walkingSpeed(1.f), isOnGround(false), animFileName("gbFighter")
{
}


BaseCharacter::~BaseCharacter()
{
}

void BaseCharacter::update(float deltaTime)
{
    BaseGameObject::update(deltaTime);

    this->setPos(this->getPos().x + moveDirection.x, this->getPos().y);

    if (this->getPos().x < 0)
    {
        this->setPos(0, this->getPos().y);
    }
    else if (this->getPos().x > 320 - 32) // todo: get rid of hardcoded values
    {
        this->setPos(320 - 32, this->getPos().y); // todo: get rid of hardcoded values
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

    // todo: get rid of hardcoded values
    if (getPos().x > 114)
    {
        isFlippedY = true;
    }
    else
    {
        isFlippedY = false;
    }

    updateState();
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
    std::string stateName;
    stateName = CharacterStateToString(currentState);
    return stateName;
}

bool BaseCharacter::getIsOnGround()
{
    return isOnGround;
}

Vector2 BaseCharacter::getMoveDirection()
{
    return moveDirection;
}
