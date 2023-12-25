//
// Created by weitnow on 12/7/23.
//

#ifndef GBFIGHTER_BASEGAMEOBJECT_H
#define GBFIGHTER_BASEGAMEOBJECT_H
#include "raylib.h"

class BaseGameObject {
public:
    BaseGameObject();
    BaseGameObject(int x, int y);
    BaseGameObject(int x, int y, float width, float height);
    ~BaseGameObject();

    void update(float deltaTime);
    void draw();

    //position
    void setPos(int x, int y);
    Vector2 getPos();

    //scale
    void setScale(int x, int y);
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

    // Define the source rectangle (which part of myTexture should be drawn)
    Rectangle sourceRect;

    // Define the destination rectangle (used for scaling the object)
    Rectangle destRect;
};


#endif //GBFIGHTER_BASEGAMEOBJECT_H
