//
// Created by weitnow on 12/7/23.
//

#ifndef GBFIGHTER_BASECHARACTER_H
#define GBFIGHTER_BASECHARACTER_H

#include "../GameObjects/BaseGameObject.h"


class BaseCharacter : public BaseGameObject {
public:
    BaseCharacter();

    BaseCharacter(int x, int y);

    ~BaseCharacter();

    void update();

    void draw();

private:
    int height;
    int width;
};





#endif //GBFIGHTER_BASECHARACTER_H
