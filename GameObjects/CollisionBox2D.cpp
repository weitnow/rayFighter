//
// Created by weitnow on 1/1/24.
//

#include "CollisionBox2D.h"
#include "../Constants.h"

CollisionBox2D::CollisionBox2D(float offsetx,
                               float offsety,
                               float width,
                               float height,
                               CollisionBoxType collisionBoxType,
                               bool isActive,
                               Color color,
                               HurtboxType hurtboxType)
    : width(width), height(height), color(color), offset{offsetx, offsety}, myRectangle{0, 0, width, height},
      objPos{0, 0}, pos{0, 0}, isActive(isActive), collisionBoxType(collisionBoxType), hurtboxType(hurtboxType)
{
}


CollisionBox2D::~CollisionBox2D()
{
}

void CollisionBox2D::update(float deltaTime)
{
    pos = {objPos.x + offset.x, objPos.y + offset.y};

    myRectangle.x = pos.x;
    myRectangle.y = pos.y;
}

void CollisionBox2D::draw()
{
#ifdef DEBUG_COLLISION_BOXES_NAMES
    // show name of the collision box
    DrawText(name.c_str(), objPos.x, objPos.y - 10, 10, color);
#endif

    DrawRectangleLinesEx(myRectangle, 1, color);
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
