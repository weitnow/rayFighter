//
// Created by weitnow on 7/21/25.
//

#ifndef DEBUG32RECTANGLE_H
#define DEBUG32RECTANGLE_H

#include "../BaseGameObject.h"


class Debug32Rectangle : public BaseGameObject
{
public:
    Debug32Rectangle(AsepriteManager* asepriteManagerPtr, float x, float y);
    virtual ~Debug32Rectangle();
    void init() override;
    void draw() override;
};


#endif //DEBUG32RECTANGLE_H
