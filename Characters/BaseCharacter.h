//
// Created by weitnow on 12/7/23.
//

#ifndef GBFIGHTER_BASECHARACTER_H
#define GBFIGHTER_BASECHARACTER_H

#include "../GameObjects/BaseGameObject.h"

enum class CharacterState
{
    Idle,
    Walk,
    Jump,
    Duck,
    Punch,
    Kick,
    Block,
    Hit,
    Hurt,
};


class BaseCharacter : public BaseGameObject
{

protected:
    // member variables
    bool isOnGround;
    float jumpForce;
    float walkingSpeed = 1.f;
    Vector2 moveDirection; // (x,y)
    CharacterState currentState;
    std::string animFileName;


    // member methodes
    void changeState(CharacterState newState);
    void updateState();

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

    /**
     * @brief Set the Current Frame Tag object
     *
     * @param tag
     * @return false if the animation is already playing, otherwise true
     */
    bool setCurrentFrameTag(std::string tag) override;

    // states
    std::string getCurrentState();
    bool getIsOnGround();
    Vector2 getMoveDirection();
};


#endif //GBFIGHTER_BASECHARACTER_H
