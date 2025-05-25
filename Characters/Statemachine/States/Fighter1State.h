#ifndef GBFIGHTER_FIGHTER1STATE_H
#define GBFIGHTER_FIGHTER1STATE_H

#include "State.h"

// Macro to declare State class methods
#define STATE_METHODS                                                                                                  \
    void Init() override;                                                                                              \
    void Update(float deltaTime) override;                                                                             \
    void Finalize() override;

class F1IdleState : public State
{
public:
    F1IdleState() : State("Idle") {};
    STATE_METHODS
};

class F1Special1State : public State
{
public:
    F1Special1State() : State("Dragonshot") {}; // using Dragonshot as Sprite
    STATE_METHODS
};

class F1Special2State : public State
{
public:
    F1Special2State() : State("A+B Move") {}; // using A+B Move as Sprite
    STATE_METHODS
};
class F1Special3State : public State
{
public:
    F1Special3State() : State("Special3") {};
    STATE_METHODS
};


#endif //GBFIGHTER_FIGHTER1STATE_H
