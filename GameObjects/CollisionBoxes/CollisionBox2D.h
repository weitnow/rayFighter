//
// Created by weitnow on 1/1/24.
//

#ifndef GBFIGHTER_COLLISIONBOX2D_H
#define GBFIGHTER_COLLISIONBOX2D_H

#include "raylib.h"
#include <string>

//forward declaration
class BaseGameObject;

enum class CollisionBoxType
{
    HITBOX,
    HURTBOX,
    PUSHBOX,
    THROWBOX,
    THROWABLEBOX,
    PROXIMITYBOX,
};

enum class HurtboxType
{
    HIGH,
    LOW,
};


class CollisionBox2D
{
public:
    CollisionBox2D(BaseGameObject* owner,
                   float offsetx,
                   float offsety,
                   float width,
                   float height,
                   float hitboxOwnerWith, // need to calculate the isFlippedX-Position of the hitbox
                   CollisionBoxType collisionBoxType = CollisionBoxType::PUSHBOX,
                   bool isActive = true,
                   Color color = BLUE,
                   HurtboxType hurtboxType = HurtboxType::HIGH);
    ~CollisionBox2D();
    void update(float deltaTime, bool isFlippedX = false);
    void draw();
    void setObjPos(float x, float y);
    Rectangle& getRectangle();

protected:
    Rectangle myRectangle;
    BaseGameObject* owner;
    Vector2 objPos;         // position of the obj which the collision box is attached to (x,y)
    Vector2 offset;         // offset from the objPos (x,y)
    Vector2 offsetFlippedX; // offset from the objPos (x,y) if the obj is flipped
    Vector2 pos;            // position of the collision box (x,y)
    float width;
    float height;
    Color color;
    bool isActive;
    CollisionBoxType collisionBoxType;
    HurtboxType hurtboxType; // only used for Hurtboxes
    bool isFlippedX;
    float hitboxOwnerWith; // need to calculate the isFlippedX-Position of the hitbox
};


#endif //GBFIGHTER_COLLISIONBOX2D_H
