//
// Created by weitnow on 1/1/24.
//

#ifndef GBFIGHTER_COLLISIONBOX2D_H
#define GBFIGHTER_COLLISIONBOX2D_H

#include "raylib.h"
#include <string>

enum class CollisionBoxType
{
    HITBOX,
    HURTBOX,
    PUSHBOX,
    THROWBOX

};

enum class HurtboxType
{
    HEAD,
    BODY,
    LEGS
};


class CollisionBox2D
{
public:
    CollisionBox2D(float offsetx,
                   float offsety,
                   float width,
                   float height,
                   CollisionBoxType collisionBoxType = CollisionBoxType::PUSHBOX,
                   bool isActive = true,
                   Color color = BLUE,
                   HurtboxType hurtboxType = HurtboxType::BODY);
    ~CollisionBox2D();
    void update(float deltaTime);
    void draw();
    void setObjPos(float x, float y);
    Rectangle& getRectangle();


protected:
    Rectangle myRectangle;
    Vector2 objPos; // position of the obj which the collision box is attached to (x,y)
    Vector2 offset; // offset from the objPos (x,y)
    Vector2 pos;    // position of the collision box (x,y)
    float width;
    float height;
    Color color;
    bool isActive;
    CollisionBoxType collisionBoxType;
    HurtboxType hurtboxType; // only used for Hurtboxes
};


#endif //GBFIGHTER_COLLISIONBOX2D_H
