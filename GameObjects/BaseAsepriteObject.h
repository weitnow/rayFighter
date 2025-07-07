//
// Created by weitnow on 7/7/25.
//

#ifndef BASEASEPRITEOBJECT_H
#define BASEASEPRITEOBJECT_H

#include "AsepriteManager.h"
#include "BaseSpriteObject.h"


class BaseAsepriteObject : public BaseSpriteObject
{
public:
    BaseAsepriteObject(AsepriteManager* asepriteManager);
    BaseAsepriteObject(AsepriteManager* asepriteManager, float x, float y);
    virtual ~BaseAsepriteObject();
    virtual void update(float deltaTime);
    virtual void draw();

    // sprites
    void addAnim(AsepriteAnimationFile* animfileptr);
    AsepriteAnimationFile* getAnimFile();
    virtual bool setCurrentFrameTag(std::string tag);
    std::string getCurrentFrameTag();


    bool getShouldDestroy();



protected:
    AsepriteManager* asepriteManagerPtr;
    AsepriteAnimationFile* animfilePtr;
    std::string currentFrameTag; // for example "gbFighter-Idle"
    bool shouldDestroy = false;
    int getDurationCurrentFrame; // Duration of the current frame in milliseconds
    int currentFrame;            // current frame of the animation
    int minFrame;                // min frame of the animation
    int maxFrame;                // max frame of the animation
    bool hasAnimFinished;        // true if the animation has just finished
    int currentFrameAbsolut;     // current frame number of the animation - min frame
};


#endif //BASEASEPRITEOBJECT_H
