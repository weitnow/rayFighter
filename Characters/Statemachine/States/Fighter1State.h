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

class F1DragenshotState : public State
{
    F1DragenshotState() : State("Dragenshot") {};
    STATE_METHODS
};



#endif //GBFIGHTER_FIGHTER1STATE_H