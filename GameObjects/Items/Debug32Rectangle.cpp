//
// Created by weitnow on 7/21/25.
//

#include "Debug32Rectangle.h"
Debug32Rectangle::Debug32Rectangle(AsepriteManager* asepriteManagerPtr, float x, float y) : BaseGameObject(asepriteManagerPtr, x, y)
{
}
Debug32Rectangle::~Debug32Rectangle()
{
}
void Debug32Rectangle::init()
{
    BaseGameObject::init();
}
void Debug32Rectangle::draw()
{
    auto myAnimFile = getAnimFile();
    myAnimFile->drawFrame("debug32", 100, 100);
    //myAnimFile->_drawFrame("debug32", 100, 100);
}