#ifndef GBFIGHTER_BASECHARACTER_H
#define GBFIGHTER_BASECHARACTER_H

#include "../GameObjects/BaseGameObject.h"
#include "../Utils/Core.h"

// Forward declaration of Statemachine
class Statemachine;

class BaseCharacter : public BaseGameObject
{

protected:
    // member variables
    bool isOnGround;
    float jumpForce;
    float walkingSpeed = 1.f;
    Vector2 moveDirection; // (x,y)
    unique<Statemachine> statemachine;
    std::string animFileName;
    bool isLeft;      // true if the character is left of the other character, only vallid for player1 or player2
    int playerNumber; // 1 or 2
    std::string currentState;

public:
    BaseCharacter(AsepriteManager* asepriteManager, float x, float y);

    virtual ~BaseCharacter();

    void update(float deltaTime);

    void draw();
    void moveLeft();
    void moveRight();
    void stop();
    void jump();
    void duck();
    void punch();

    void setIsLeft(bool isLeft);
    bool getIsLeft();

    void setPlayerNumber(int playerNumber);
    int getPlayerNumber();

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
