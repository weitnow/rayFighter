//
// Created by weitnow on 12/7/23.
//

#ifndef GBFIGHTER_BASECHARACTER_H
#define GBFIGHTER_BASECHARACTER_H

#include "../GameObjects/BaseGameObject.h"


class BaseCharacter : public BaseGameObject
{

private:
    // member variables
    bool isJumping;
    float jumpHeight;
    float jumpSpeed;
    float gravity;
    float jumpTime;
    float jumpTimeCounter;
    float walkingSpeed = 1.f;

public:
    BaseCharacter();

    BaseCharacter(float x, float y);

    ~BaseCharacter();

    void update(float deltaTime);

    void draw();

    void moveLeft();
    void moveRight();
    void jump();
};


#endif //GBFIGHTER_BASECHARACTER_H
