//
// Created by weitnow on 12/7/23.
//

#include "BaseCharacter.h"
#include "../Constants.h"


BaseCharacter::BaseCharacter(AsepriteManager* asepriteManager) : BaseGameObject(asepriteManager)
{
}

BaseCharacter::BaseCharacter(AsepriteManager* asepriteManager, float x, float y) : BaseGameObject(asepriteManager, x, y)
{
    this->moveDirection = {0, 0};
    this->jumpForce = 4.4f;
    this->walkingSpeed = 1.f;
    this->isOnGround = false;
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
    if (this->getPos().y > Constants::BASELINE)
    {
        this->isOnGround = true;
        this->setPos(this->getPos().x, Constants::BASELINE);
        this->moveDirection.y = 0;
    }
    else
    //if character is not on the ground, fall
    {
        this->moveDirection.y += Global::gravity * deltaTime;
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
