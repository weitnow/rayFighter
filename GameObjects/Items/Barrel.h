#ifndef GBFIGHTER_BARREL_H
#define GBFIGHTER_BARREL_H

#include "../BaseGameObject.h"

class Barrel : public BaseGameObject
{
public:
    Barrel(AsepriteManager* asepriteManager, float x, float y);
    virtual ~Barrel();

    virtual void update(float deltaTime) override;
    virtual void takeDamage(float damage = 1.f) override;

    virtual void init() override;


private:
    virtual void _reducePushVector(float deltaTime) override;
};


#endif //GBFIGHTER_BARREL_H
