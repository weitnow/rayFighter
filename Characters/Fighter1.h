#ifndef GBFIGHTER_FIGHTER1_H
#define GBFIGHTER_FIGHTER1_H

#include "BaseCharacter.h"


class Fighter1 : public BaseCharacter
{
public:
    Fighter1(AsepriteManager* asepriteManager, float x, float y);
    ~Fighter1();
    virtual void init() override;
};


#endif //GBFIGHTER_FIGHTER1_H
