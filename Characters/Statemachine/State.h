#ifndef GBFIGHTER_STATE_H
#define GBFIGHTER_STATE_H

#include "../BaseCharacter.h"
#include <iostream>

class State
{
public:
    virtual ~State() = default;

    // Pure virtual methods to be implemented by derived classes
    virtual void Init() = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void Finalize() = 0;

    std::string stateName = "default";

    virtual void setOwner(BaseCharacter* owner)
    {
        this->owner = owner;
    }

protected:
    BaseCharacter* owner = nullptr; // Pointer to the BaseCharacter owning this state
};

// Macro to declare State class methods
#define STATE_METHODS                                                                                                  \
    void Init() override;                                                                                              \
    void Update(float deltaTime) override;                                                                             \
    void Finalize() override;

// Derived state classes using the macro
class IdleState : public State
{
    STATE_METHODS
};
class WalkState : public State
{
    STATE_METHODS
};
class JumpState : public State
{
    STATE_METHODS
};
class DuckState : public State
{
    STATE_METHODS
};
class PunchState : public State
{
    STATE_METHODS
};
class KickState : public State
{
    STATE_METHODS
};
class BlockState : public State
{
    STATE_METHODS
};

class HitState : public State
{
    STATE_METHODS
};

class HurtState : public State
{
    STATE_METHODS
};

#undef STATE_METHODS

#endif //GBFIGHTER_STATE_H
