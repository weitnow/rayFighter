#ifndef GBFIGHTER_TITLESCREEN_H
#define GBFIGHTER_TITLESCREEN_H

#include "../GameObjects/BaseSpriteObject.h"

class Titlescreen : public BaseSpriteObject
{
public:
    Titlescreen(float x = 0, float y = 0) : BaseSpriteObject(x, y, "Assets/Graphics/titlescreen.png")
    {
    }
};

#endif
