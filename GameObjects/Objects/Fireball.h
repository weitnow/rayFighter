#include "../BaseGameObject.h"
#ifndef GBFIGHTER_FIREBALL_H
#define GBFIGHTER_FIREBALL_H
#include <string>

class Fireball : public BaseGameObject
{
public:
    Fireball(AsepriteManager* asepriteManagerPtr, float x, float y, bool isFlippedX = false);


    void update(float deltaTime) override;

    void handleHitLogic(List<CollisionBox2D*>& hitboxesThatHit, List<CollisionBox2D*>& hurtboxesThatWereHit, BaseGameObject& otherGameObject) override;
};


#endif //GBFIGHTER_FIREBALL_H
