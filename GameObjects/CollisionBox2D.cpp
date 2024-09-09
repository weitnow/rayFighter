//
// Created by weitnow on 1/1/24.
//

#include "CollisionBox2D.h"
#include "../Constants.h"

CollisionBox2D::CollisionBox2D()
    : name("CollisionBox2D"), width(16.0f), height(16.0f), color(Colors::getRedTransparent())
{
}

CollisionBox2D::CollisionBox2D(std::string name, float x, float y, float width, float height, Color color)
    : name(name), width(width), height(height), color(color)
{
    pos.x = x;
    pos.y = y;
    myRectangle = {pos.x, pos.y, width, height};
}

CollisionBox2D::~CollisionBox2D()
{
}

void CollisionBox2D::update(float deltaTime)
{
    myRectangle.x = pos.x;
    myRectangle.y = pos.y;
}

void CollisionBox2D::draw()
{
#ifdef DEBUG_COLLISION_BOXES_NAMES
    // show name of the collision box
    DrawText(name.c_str(), pos.x, pos.y - 10, 10, color);
#endif

    DrawRectangleLinesEx(myRectangle, 1, color);
}

void CollisionBox2D::setPos(float x, float y)
{
    pos.x = x;
    pos.y = y;
}
