//
// Created by weitnow on 7/7/25.
//

#ifndef BASEASEPRITEOBJECT_H
#define BASEASEPRITEOBJECT_H

#include "BaseSpriteObject.h"



class BaseAsepriteObject : public BaseSpriteObject
{
    public:
        BaseAsepriteObject();
    BaseAsepriteObject(float x, float y, bool isFlippedX = false);
        ~BaseAsepriteObject();

};



#endif //BASEASEPRITEOBJECT_H
