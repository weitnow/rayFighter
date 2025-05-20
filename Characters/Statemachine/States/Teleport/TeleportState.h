#ifndef GBFIGHTER_TELEPORTSTATE_H
#define GBFIGHTER_TELEPORTSTATE_H

#include "../State.h"

// Macro to declare State class methods
#define STATE_METHODS                                                                                                  \
    void Init() override;                                                                                              \
    void Update(float deltaTime) override;                                                                             \
    void Finalize() override;


class TeleportState : public State
{
public:
    TeleportState() : State("Idle") {};
    STATE_METHODS
};



#endif //GBFIGHTER_TELEPORTSTATE_H