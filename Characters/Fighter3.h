#ifndef GBFIGHTER_FIGHTER3_H
#define GBFIGHTER_FIGHTER3_H

#include "BaseCharacter.h"


class Fighter3 : public BaseCharacter
{
public:
    Fighter3(AsepriteManager* asepriteManager, float x, float y);
    ~Fighter3();
    virtual void init() override;
};


#endif //GBFIGHTER_FIGHTER3_H
