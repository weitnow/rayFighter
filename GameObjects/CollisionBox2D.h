//
// Created by weitnow on 1/1/24.
//

#ifndef GBFIGHTER_COLLISIONBOX2D_H
#define GBFIGHTER_COLLISIONBOX2D_H

#include "raylib.h"
#include <string>


class CollisionBox2D
{
public:
    CollisionBox2D();
    CollisionBox2D(std::string name, float offsetx, float offsety, float width, float height, Color color = BLUE);
    ~CollisionBox2D();
    void update(float deltaTime);
    void draw();
    void setObjPos(float x, float y);
    Rectangle& getRectangle();

protected:
    Rectangle myRectangle;
    Vector2 objPos; // position of the obj which the collision box is attached to
    Vector2 offset; // offset from the objPos
    Vector2 pos;    // position of the collision box
    float width;
    float height;
    Color color;
    std::string name;
};


#endif //GBFIGHTER_COLLISIONBOX2D_H
