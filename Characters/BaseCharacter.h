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
    virtual void init() override;
    virtual void update(float deltaTime) override;
    void draw();
    //void moveLeft();  // implemented in BaseGameObject
    //void moveRight(); // implemented in BaseGameObject
    //void stop();      // implemented in BaseGameObject
    void jump();
    void duck();
    void punch();

    virtual void takeDamage(float damage, CollisionBox2D* hitbox) override;

    void setIsLeft(bool isLeft);
    bool getIsLeft();

    virtual void setMoveVectorY(int yValue) override;
    //void setMoveVectorX   // implemented in BaseGameObject
    //void setMoveVector    // implemented in BaseGameObject

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

    // Todo: refactor this to private
    bool canDealDamage;


protected:
    // member variables
    bool isOnGround;
    float jumpForce = 300.f;
    // BaseGameObject::moveSpeed = 60.f
    unique<Statemachine> statemachine;
    std::string animFileName;
    bool isLeft;      // true if the character is left of the other character, only vallid for player1 or player2
    int playerNumber; // 1 or 2
    std::string currentState;

    CharacterController* controller;

    // member functions
    virtual void _applyGravity(float deltaTime) override;
};


#endif //GBFIGHTER_BASECHARACTER_H
