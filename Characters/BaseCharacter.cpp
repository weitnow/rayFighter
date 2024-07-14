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
}

void BaseCharacter::draw()
{
    BaseGameObject::draw();
}

void BaseCharacter::moveLeft()
{
    this->setPos(this->getPos().x - walkingSpeed, this->getPos().y);
}

void BaseCharacter::moveRight()
{
    this->setPos(this->getPos().x + walkingSpeed, this->getPos().y);
}

void BaseCharacter::jump()
{
}
