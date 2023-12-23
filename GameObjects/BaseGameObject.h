//
// Created by weitnow on 12/7/23.
//

#ifndef GBFIGHTER_BASEGAMEOBJECT_H
#define GBFIGHTER_BASEGAMEOBJECT_H
#include "raylib.h"

class BaseGameObject {
public:
    BaseGameObject();
    ~BaseGameObject();
    void update();
    void draw();
    void setPos(int x, int y);

protected:
    Vector2 pos;
};


#endif //GBFIGHTER_BASEGAMEOBJECT_H
