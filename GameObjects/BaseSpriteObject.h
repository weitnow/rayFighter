#ifndef GBFIGHTER_BASESPRITEOBJECT_H
#define GBFIGHTER_BASESPRITEOBJECT_H
#include "../Utils/Core.h"
#include "CollisionBoxes/CollisionBox2D.h"

#include <functional> // used for tween function
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
    void setPos(float x, float y); // topleftCorner
    void setPos(Vector2 pos); // topleftCorner
    Vector2 getPos(); // topleftCorner
    void setCenterPos(float x, float y);
    void setCenterPos(Vector2 pos);
    Vector2 getCenterPos();

    void moveTowards(Vector2 target, float speed, std::function<float(float)> tweenFunc);

    //texture
    void loadTexture(const std::string& texturePath);

    //scale
    void setScale(int scaleLevel);
    int getScale();

    // orientation
    void setIsFlippedX(bool flipX);
    void setIsFlippedY(bool flipY);
    bool getIsFlippedX();
    bool getIsFlippedY();

    // rotation
    void setRotation(int rotation);
    int getRotation();

protected:
    // Define the origin point for rotation (the center of the rectangle)
    Vector2 origin;
    float rotation;
    Vector2 pos;
    int scale;
    Texture2D myTexture;

    // a 32x32 Texture which will be drawn in debug-mode
    Texture2D myDebug32x32Texture;

    // Define the source rectangle (which part of myTexture should be drawn)
    Rectangle sourceRect;

    // Define the destination rectangle (used for scaling the object)
    Rectangle destRect;

    bool isFlippedX = false;
    bool isFlippedY = false;

    // member variables used for moveTowards
    bool isMoving = false;
    Vector2 moveStartPos;
    Vector2 moveTargetPos;
    float moveElapsed = 0.0f;
    float moveSpeed = 0.0f;
    float moveTotalDistance = 0.0f;
    std::function<float(float)> moveTweenFunc;
};


#endif //GBFIGHTER_BASESPRITEOBJECT_H
