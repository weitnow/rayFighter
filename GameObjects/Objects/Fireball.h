#ifndef GBFIGHTER_FIREBALL_H
#define GBFIGHTER_FIREBALL_H

#include "../BaseGameObject.h"


class Fireball : public BaseGameObject
{
public:
    Fireball(AsepriteManager* asepriteManagerPtr, float x, float y, bool isFlippedX = false);


    void update(float deltaTime) override;

    void handleHitLogic(vector<CollisionBox2D*>& hitboxesThatHit, vector<CollisionBox2D*>& hurtboxesThatWereHit, BaseGameObject& otherGameObject) override;
};


#endif //GBFIGHTER_FIREBALL_H
