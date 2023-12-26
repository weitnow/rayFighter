//
// Created by weitnow on 12/7/23.
//

#ifndef GBFIGHTER_BASEGAMEOBJECT_H
#define GBFIGHTER_BASEGAMEOBJECT_H
#include "raylib.h"

class BaseGameObject {
public:
    BaseGameObject();
    BaseGameObject(float x, float y);
    BaseGameObject(float x, float y, float width, float height);
    ~BaseGameObject();

    void update(float deltaTime);
    void draw();

    //position
    void setPos(float x, float y);
    void setPos(Vector2 pos);
    Vector2 getPos();

    //scale
    void setScale(float x, float y);
    void setScale(Vector2 scale);
    Vector2 getScale();

protected:
    float height;
    float width;
    float scalex;
    float scaley;

    // Define the origin point for rotation (the center of the rectangle)
    Vector2 origin;

    float rotation;
    Vector2 pos;
    Vector2 scale;
    Texture2D myTexture;
    Texture2D myDebug32x32Texture;

    // Define the source rectangle (which part of myTexture should be drawn)
    Rectangle sourceRect;

    // Define the destination rectangle (used for scaling the object)
    Rectangle destRect;
};


#endif //GBFIGHTER_BASEGAMEOBJECT_H
