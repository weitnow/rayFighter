#ifndef GBFIGHTER_BASESPRITEOBJECT_H
#define GBFIGHTER_BASESPRITEOBJECT_H
#include "../Utils/Core.h"
#include "CollisionBox2D.h"
#include <map>
#include <raylib.h>
#include <string>

class BaseSpriteObject
{
public:
    BaseSpriteObject();
    BaseSpriteObject(float x, float y, const std::string& texturePath = "Assets/Graphics/debug32x32.png");
    ~BaseSpriteObject();

    void update(float deltaTime);
    void draw();

    //position
    void setPos(float x, float y);
    void setPos(Vector2 pos);
    Vector2 getPos();

    //texture
    void loadTexture(const std::string& texturePath);

    //scale
    void setScale(float x, float y);
    void setScale(Vector2 scale);
    Vector2 getScale();

protected:
    // Define the origin point for rotation (the center of the rectangle)
    Vector2 origin;
    float rotation;
    Vector2 pos;
    Vector2 scale;
    Texture2D myTexture;

    // a 32x32 Texture which will be drawn in debug-mode
    Texture2D myDebug32x32Texture;

    // Define the source rectangle (which part of myTexture should be drawn)
    Rectangle sourceRect;

    // Define the destination rectangle (used for scaling the object)
    Rectangle destRect;
};


#endif //GBFIGHTER_BASESPRITEOBJECT_H
