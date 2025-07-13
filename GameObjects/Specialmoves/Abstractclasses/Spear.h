//
// Created by weitnow on 7/5/25.
//

#ifndef SPEAR_H
#define SPEAR_H
#include "BaseGameObject.h"


class Spear : public BaseGameObject
{

public:
    Spear(AsepriteManager* asepriteManagerPtr, float x, float y, bool isFlippedX = false);

    void update(float deltaTime) override;

    void handleHitLogic(vector<CollisionBox2D*>& hitboxesThatHit,
                        vector<CollisionBox2D*>& hurtboxesThatWereHit,
                        BaseGameObject& otherGameObject) override;

    void handleYouInteractLogic(vector<CollisionBox2D*>& throwBoxThatHit, vector<CollisionBox2D*>& throwableBoxThatWereHit, BaseGameObject& otherGameObject) override;

    void draw() override;

protected:
    bool movingRight;

    std::vector<unique<BaseAsepriteObject>> myAsepriteObjects;

};



#endif //SPEAR_H
