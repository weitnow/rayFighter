//
// Created by weitnow on 12/7/23.
//

#ifndef GBFIGHTER_BASECHARACTER_H
#define GBFIGHTER_BASECHARACTER_H

#include "../GameObjects/BaseGameObject.h"


class BaseCharacter : public BaseGameObject {
public:
    BaseCharacter();

    BaseCharacter(float x, float y);

    ~BaseCharacter();

    void update(float deltaTime);

    void draw();

};





#endif //GBFIGHTER_BASECHARACTER_H
