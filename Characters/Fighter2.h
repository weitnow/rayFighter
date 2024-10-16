#ifndef GBFIGHTER_FIGHTER2_H
#define GBFIGHTER_FIGHTER2_H

#include "BaseCharacter.h"


class Fighter2 : public BaseCharacter
{
public:
    Fighter2(AsepriteManager* asepriteManager, float x, float y);
    ~Fighter2();
    virtual void init() override;
};


#endif //GBFIGHTER_FIGHTER2_H
