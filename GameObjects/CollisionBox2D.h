//
// Created by weitnow on 1/1/24.
//

#ifndef GBFIGHTER_COLLISIONBOX2D_H
#define GBFIGHTER_COLLISIONBOX2D_H

#include "raylib.h"


class CollisionBox2D {
public:
    CollisionBox2D();
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
};


#endif //GBFIGHTER_COLLISIONBOX2D_H
