//
// Created by weitnow on 12/7/23.
//

#ifndef GBFIGHTER_BASECHARACTER_H
#define GBFIGHTER_BASECHARACTER_H

#include "../GameObjects/BaseGameObject.h"


class BaseCharacter : public BaseGameObject
{

protected:
    // member variables
    bool isOnGround;
    float jumpForce;
    float walkingSpeed = 1.f;
    Vector2 moveDirection; // (x,y)

public:
    BaseCharacter(AsepriteManager* asepriteManager);

    BaseCharacter(AsepriteManager* asepriteManager, float x, float y);

    virtual ~BaseCharacter();

    void update(float deltaTime);

    void draw();

    void moveLeft();
    void moveRight();
    void stop();
    void jump();
    void duck();
};


#endif //GBFIGHTER_BASECHARACTER_H
