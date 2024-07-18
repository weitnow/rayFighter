//
// Created by weitnow on 12/7/23.
//

#include "BaseCharacter.h"


BaseCharacter::BaseCharacter() : BaseGameObject()
{
}

BaseCharacter::BaseCharacter(float x, float y) : BaseGameObject(x, y)
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
}

void BaseCharacter::duck()
{
}
