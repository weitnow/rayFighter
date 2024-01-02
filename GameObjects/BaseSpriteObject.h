//
// Created by weitnow on 12/7/23.
//

#ifndef GBFIGHTER_BASESPRITEOBJECT_H
#define GBFIGHTER_BASESPRITEOBJECT_H
#include "raylib.h"
#include "CollisionBox2D.h"
#include <map>
#include <string>

class BaseSpriteObject {
public:
    BaseSpriteObject();
    BaseSpriteObject(float x, float y);
    BaseSpriteObject(float x, float y, float width, float height);
    ~BaseSpriteObject();

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

    //hitboxes
    void addCollisionBox(std::string hitboxName);

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

    std::map<std::string, CollisionBox2D> collisionboxes;
};


#endif //GBFIGHTER_BASESPRITEOBJECT_H
