//
// Created by weitnow on 1/1/24.
//

#include "CollisionBox2D.h"
#include "../Constants.h"

#include <iostream> // get rid just for debbuging needed

CollisionBox2D::CollisionBox2D(float offsetx,
                               float offsety,
                               float width,
                               float height,
                               CollisionBoxType collisionBoxType,
                               bool isActive,
                               Color color,
                               HurtboxType hurtboxType)
    : width(width), height(height), color(color), offset{offsetx, offsety}, myRectangle{0, 0, width, height},
      objPos{0, 0}, pos{0, 0}, isActive(isActive), collisionBoxType(collisionBoxType), hurtboxType(hurtboxType),
      isFlippedX(false)
{
    float flippedX = abs(32.f - offsetx - width);
    offsetFlippedX = {flippedX, offsety};
}


CollisionBox2D::~CollisionBox2D()
{
}

void CollisionBox2D::update(float deltaTime, bool isFlippedX)
{
    this->isFlippedX = isFlippedX;

    if (!isFlippedX)
    {
        pos = {objPos.x + offset.x, objPos.y + offset.y};
    }
    else
    {
        pos = {objPos.x + offsetFlippedX.x, objPos.y + offset.y};
    }


    //pos = {objPos.x + offset.x, objPos.y + offset.y};

    myRectangle.x = pos.x;
    myRectangle.y = pos.y;
}

void CollisionBox2D::draw()
{
    DrawRectangleLinesEx(myRectangle, 1, color);
    if (collisionBoxType == CollisionBoxType::HITBOX)
    {
        std::cout << "Is flipped X: " << isFlippedX << std::endl;
        std::cout << myRectangle.x << std::endl;
    }
}

void CollisionBox2D::setObjPos(float x, float y)
{
    objPos.x = x;
    objPos.y = y;
}

Rectangle& CollisionBox2D::getRectangle()
{
    return myRectangle;
}
