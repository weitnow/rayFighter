#ifndef GBFIGHTER_BASECHARACTER_H
#define GBFIGHTER_BASECHARACTER_H

#include "../GameObjects/BaseGameObject.h"
#include "../Utils/Core.h"
//#include "../Utils/InputHandler.h"
// Forward declaration of CharacterController
class CharacterController;
// Forward declaration of Statemachine
class Statemachine;

class BaseCharacter : public BaseGameObject
{
public:
    BaseCharacter(AsepriteManager* asepriteManager, float x, float y);

    virtual ~BaseCharacter();

    virtual void update(float deltaTime) override;
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

    void addController(CharacterController* controller);
    CharacterController* getController();

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
    Vector2 getMoveVector();
    Statemachine& getStatemachine();


protected:
    // member variables
    bool isOnGround;
    float jumpForce = 300.f;
    float walkingSpeed = 60.f;
    unique<Statemachine> statemachine;
    std::string animFileName;
    bool isLeft;      // true if the character is left of the other character, only vallid for player1 or player2
    int playerNumber; // 1 or 2
    std::string currentState;

    CharacterController* controller;

    // member functions
    virtual void _applyGravity(float deltaTime) override;
    void _keepOnStage();
};


#endif //GBFIGHTER_BASECHARACTER_H
