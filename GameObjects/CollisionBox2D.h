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
    CollisionBox2D(std::string name, float x, float y, float width, float height, Color color = BLUE);
    ~CollisionBox2D();
    void update(float deltaTime);
    void draw();
    void setPos(float x, float y);

protected:
    Rectangle myRectangle;
    Vector2 pos;
    float width;
    float height;
    Color color;
    std::string name;
};


#endif //GBFIGHTER_COLLISIONBOX2D_H
