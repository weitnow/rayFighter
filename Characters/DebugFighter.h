#ifndef GBFIGHTER_DEBUGFIGHTER_H
#define GBFIGHTER_DEBUGFIGHTER_H

#include "BaseCharacter.h"


class DebugFighter : public BaseCharacter
{
public:
    DebugFighter(AsepriteManager* asepriteManager, float x, float y);
    ~DebugFighter();
    virtual void init() override;
};


#endif //GBFIGHTER_DEBUGFIGHTER_H
