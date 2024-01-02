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

    // a map which holds all the collisionbox-obj
    std::map<std::string, CollisionBox2D> collisionboxes;
};


#endif //GBFIGHTER_BASESPRITEOBJECT_H
