
#ifndef GBFIGHTER_BASEGAMEOBJECT_H
#define GBFIGHTER_BASEGAMEOBJECT_H

#include "../Utils/AsepriteManager.h"
#include "../Utils/Core.h"
#include "BaseSpriteObject.h"
#include "CollisionBox2D.h"
#include <raylib.h>

// Using directive to shorten the type name
using CollisionMap = Dictionary<std::string, List<CollisionBox2D>>;

class BaseGameObject
{
public:
    BaseGameObject(AsepriteManager* asepriteManager);
    BaseGameObject(AsepriteManager* asepriteManager, float x, float y);
    virtual ~BaseGameObject();

    virtual void update(float deltaTime);
    virtual void draw();

    virtual void takeDamage(float damage = 1.f);
    virtual void takeDamage(float damage, CollisionBox2D* hitbox);

    int& getCurrentLife();
    bool getIsAlive();
    bool getIsActive();

    void setLife(int currentLife);

    void setObjName(std::string name);
    std::string getObjName();

    // position
    void setPos(float x, float y);
    void setPos(Vector2 pos);
    virtual Vector2 getPos() const;

    //gravity
    void setAffectedByGravity(bool affectedByGravity);

    // scale
    void setScale(float scale);
    float getScale();

    // sprites
    void addAnim(AsepriteAnimationFile* animfileptr);
    AsepriteAnimationFile* getAnim();
    virtual bool setCurrentFrameTag(std::string tag);
    std::string getCurrentFrameTag();

    List<CollisionBox2D> getPushBoxes();
    List<CollisionBox2D> getHitBoxes();
    List<CollisionBox2D> getHurtBoxes();
    List<CollisionBox2D> getThrowBoxes();


    // HitBoxes
    void addCollisionBoxForFrame(const std::string frameTag,
                                 int frameNumber,
                                 CollisionBoxType collisionBoxType,
                                 HurtboxType hurtboxType,
                                 bool isActive,
                                 float offsetX,
                                 float offsetY,
                                 float width,
                                 float height);

    void addCollisionBoxForFrame(const std::string frameTag,
                                 int frameNumber,
                                 CollisionBoxType collisionBoxType,
                                 bool isActive,
                                 float offsetX,
                                 float offsetY,
                                 float width,
                                 float height);


    //pushVector
    void setPushVector(Vector2 pushVector);
    Vector2 getPushVector();
    void resetPushVector();

    //moveVector
    virtual void setMoveVectorY(int yValue);

protected:
    Vector2 orginalPos; // the original position of the object as it was created - used for reseting the object
    Vector2 pos;
    Vector2 moveVector; // (x,y)
    float scale;
    Color color;
    bool isFlippedX;
    bool isFlippedY;
    std::string currentFrameTag; // for example "gbFighter-Idle"
    std::string ObjName;         // for example "Andy"
    bool isActive;
    bool isAlive; // if life is < 0 takeDamage will set isAlive = false
    bool isInvincible;
    int getDurationCurrentFrame; // Duration of the current frame in milliseconds
    int currentFrame;            // current frame of the animation
    int minFrame;                // min frame of the animation
    int maxFrame;                // max frame of the animation
    bool hasAnimJustFinished;    // true if the animation has just finished
    int currentFrameAbsolut;     // current frame number of the animation - min frame
    int life;

    float _invincibleCounter;
    float invincibleTime;
    bool affectedByGravity;

    // CollisionMap holds collisionBoxes per frame like this: collisionBoxesPerFrame["gbFighter-Idle"][0] = List<CollisionBox2D>
    CollisionMap hitBoxesPerFrame;
    CollisionMap hurtBoxesPerFrame;
    CollisionMap pushBoxesPerFrame;
    CollisionMap throwBoxesPerFrame;

    Vector2 pushVector;

    AsepriteAnimationFile* animfilePtr;
    AsepriteManager* asepriteManagerPtr;

    // member functions
    virtual void _reducePushVector(float deltaTime);
    virtual void _applyGravity(float deltaTime);
    void _updateMemberVariables(); // update member variables from the animationfile
    void _updateCollisionBoxes(float deltaTime);
    void _drawCollisionBoxes();
    void _addCollisionBoxForFrameInternal(std::string frameTagName,
                                          int offsetX,
                                          int offsetY,
                                          int width,
                                          int height,
                                          CollisionBoxType collisionBoxType,
                                          HurtboxType hurtboxType,
                                          bool isActive);

    List<CollisionBox2D> _checkIfCollisionMapHasCollisionBoxesAndReturnList(const std::string& currentFrameTag,
                                                                            const int currentFrameAbsolut,
                                                                            CollisionBoxType collisionBoxType);
};

#endif // GBFIGHTER_BASEGAMEOBJECT_H
