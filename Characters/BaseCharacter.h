//
// Created by weitnow on 12/7/23.
//

#ifndef GBFIGHTER_BASECHARACTER_H
#define GBFIGHTER_BASECHARACTER_H

#include "../GameObjects/BaseSpriteObject.h"


class BaseCharacter : public BaseSpriteObject {
public:
    BaseCharacter();

    BaseCharacter(float x, float y);

    ~BaseCharacter();

    void update(float deltaTime);

    void draw();

};





#endif //GBFIGHTER_BASECHARACTER_H
