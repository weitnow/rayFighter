#ifndef GBFIGHTER_STATE_H
#define GBFIGHTER_STATE_H


#include "../BaseCharacter.h"
#include <iostream>

// Forward declaration of InputHandler (CharacterController)
class CharacterController;

class State
{
public:
    explicit State(const std::string& name) : stateName(name)
    {
#ifdef DEBUG
        std::cout << "State '" << stateName << "' created" << std::endl;
#endif
    }

    virtual ~State()
    {
#ifdef DEBUG
        std::cout << "State '" << stateName << "' destroyed" << std::endl;
#endif
    }
    // Pure virtual methods to be implemented by derived classes
    virtual void Init() = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void Finalize() = 0;

    virtual void setOwner(BaseCharacter* owner);
    std::string stateName = "default";

protected:
    BaseCharacter* owner = nullptr;            // Pointer to the BaseCharacter owning this state
    CharacterController* controller = nullptr; // Pointer to the CharacterController
    Statemachine* statemachine = nullptr;      // Pointer to the Statemachine
    float timer = 0;
};

// Macro to declare State class methods
#define STATE_METHODS                                                                                                  \
    void Init() override;                                                                                              \
    void Update(float deltaTime) override;                                                                             \
    void Finalize() override;

// Derived state classes using the macro
class IdleState : public State
{
public:
    IdleState() : State("Idle") {};
    STATE_METHODS
};
class WalkState : public State
{
public:
    WalkState() : State("Walk") {};
    STATE_METHODS
};
class JumpState : public State
{
public:
    JumpState() : State("Jump") {};
    STATE_METHODS
private:
    bool alreadyJumped = false;
    bool goRight = false;
    bool goLeft = false;
};
class DuckState : public State
{
public:
    DuckState() : State("Duck") {};
    STATE_METHODS
};
class PunchState : public State
{
public:
    PunchState() : State("Punch") {};
    STATE_METHODS
};
class KickState : public State
{
public:
    KickState() : State("Kick") {};
    STATE_METHODS
};
class BlockState : public State
{
public:
    BlockState() : State("Block") {};
    STATE_METHODS
};

class HitState : public State
{
public:
    HitState() : State("Hit") {};
    STATE_METHODS
};

class HurtState : public State
{
public:
    HurtState() : State("Hurt") {};
    STATE_METHODS
};

class DeathState : public State
{
public:
    DeathState() : State("Death") {};
    STATE_METHODS
};

#undef STATE_METHODS

#endif //GBFIGHTER_STATE_H
