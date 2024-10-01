
#ifndef GBFIGHTER_BASEGAMEOBJECT_H
#define GBFIGHTER_BASEGAMEOBJECT_H

#include "../Utils/AsepriteManager.h"
#include "../Utils/Core.h"
#include "BaseSpriteObject.h"
#include "CollisionBox2D.h"
#include <raylib.h>

class BaseGameObject
{
public:
    BaseGameObject(AsepriteManager* asepriteManager);
    BaseGameObject(AsepriteManager* asepriteManager, float x, float y);
    virtual ~BaseGameObject();

    virtual void update(float deltaTime);
    virtual void draw();

    void setObjName(std::string name);
    std::string getObjName();

    // position
    void setPos(float x, float y);
    void setPos(Vector2 pos);
    virtual Vector2 getPos() const;

    // scale
    void setScale(float scale);
    float getScale();

    // sprites
    void addAnim(AsepriteAnimationFile* animfileptr);
    AsepriteAnimationFile* getAnim();
    virtual bool setCurrentFrameTag(std::string tag);
    std::string getCurrentFrameTag();

    // hitboxes
    void addCollisionBox(std::string hitboxName,
                         float x,
                         float y,
                         float width,
                         float height,
                         CollisionBoxType collisionBoxType = CollisionBoxType::PUSHBOX,
                         bool isActive = true,
                         Color color = BLUE);
    void removeCollisionBox(std::string hitboxName);

    // collision boxes
    Dictionary<std::string, CollisionBox2D>& getCollisionBoxes();

    //pushVector
    void setPushVector(Vector2 pushVector);
    Vector2 getPushVector();
    void resetPushVector();

protected:
    Vector2 pos;
    float scale;
    Color color;
    bool isFlippedX;
    bool isFlippedY;
    std::string currentFrameTag;
    std::string ObjName;

    Vector2 pushVector;

    // a map which holds all the sprite-objs
    Dictionary<std::string, BaseSpriteObject> sprites;

    AsepriteAnimationFile* animfilePtr;
    AsepriteManager* asepriteManagerPtr;


    // a map which holds all the collisionbox-objs
    Dictionary<std::string, CollisionBox2D> collisionBoxes;
};

#endif // GBFIGHTER_BASEGAMEOBJECT_H
