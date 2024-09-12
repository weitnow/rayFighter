//
// Created by weitnow on 1/1/24.
//

#include "CollisionBox2D.h"
#include "../Constants.h"

CollisionBox2D::CollisionBox2D()
    : name("CollisionBox2D"), width(16.0f), height(16.0f), color(Colors::getRedTransparent())
{
}

CollisionBox2D::CollisionBox2D(std::string name, float offsetx, float offsety, float width, float height, Color color)
    : name(name), width(width), height(height), color(color)
{
    offset.x = offsetx;
    offset.y = offsety;
    myRectangle = {0, 0, width, height};
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
