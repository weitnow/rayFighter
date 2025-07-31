#ifndef GBFIGHTER_BASECHARACTER_H
#define GBFIGHTER_BASECHARACTER_H

#include "../GameObjects/BaseGameObject.h"
#include "../Utils/Core.h"
#include "../Utils/Input/InputTypes.h"

//#include "../Utils/InputHandler.h"
// Forward declaration of CharacterController
class CharacterController;
// Forward declaration of Statemachine
class Statemachine;

class BaseCharacter : public BaseGameObject
{
public:
    BaseCharacter(AsepriteManager* asepriteManager, float x, float y, const std::string& initialFrameTag);
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

    void setIsLeft(bool isLeft);
    bool getIsLeft();

    virtual void setMoveVectorY(int yValue) override;
    //void setMoveVectorX   // implemented in BaseGameObject
    //void setMoveVector    // implemented in BaseGameObject

    void setPlayerNumber(int playerNumber);
    int getPlayerNumber();

    void addController(CharacterController* controller);
    CharacterController* getController();

    // states
    std::string getCurrentState();
    bool getIsOnGround();
    Vector2 getMoveVector();
    Statemachine& getStatemachine();




    // if true, the character will automatically set the frameTag in ints update function which triggers the animation,
    // this will be set to false in the states for special attacks
    bool automaticallySetFrameTag = true;

    void setMaxPowerLevel(int maxPowerLevel); // use only for initialization
    int getMaxPowerLevel();                   // use only for initialization

    void setPowerLevel(int powerLevel);
    int getPowerLevel();

    // special moves
    virtual const std::vector<SpecialMove>& getSpecialMoves() const;


protected:
    // member variables

    bool isOnGround;
    float jumpForce = 300.f;
    // BaseGameObject::moveSpeed = 60.f
    unique<Statemachine> statemachine;
    bool isLeft;      // true if the character is left of the other character, only valid for player1 or player2
    int playerNumber; // 1 or 2
    std::string currentState;

    CharacterController* controller;

    int maxPowerLevel;
    int powerLevel;

    // special moves
    std::vector<SpecialMove> specialMoves = {};

    // member functions
    virtual void _applyGravity(float deltaTime) override;
    void _updateCharacterController(); //updates bool isLeft in CharacterController

    void handleHitLogic(vector<CollisionBox2D*>& hitboxesThatHit, vector<CollisionBox2D*>& hurtboxesThatWereHit, BaseGameObject& otherGameObject) override;
    void handleGotHitLogic(vector<CollisionBox2D*>& hitboxesThatHit, vector<CollisionBox2D*>& hurtboxesThatWereHit, BaseGameObject& otherGameObject) override;
};


#endif //GBFIGHTER_BASECHARACTER_H
