#ifndef GBFIGHTER_ASEPRITEMANAGER_H
#define GBFIGHTER_ASEPRITEMANAGER_H

#include "../Constants.h"
#include "../nlohmann/json.hpp"
#include "Core.h"
#include "raylib.h"
#include <fstream>
#include <iostream>
#include <map>
#include <string>

struct FrameTag;       // forward declaration
class AsepriteManager; //forward declaration

struct OffSets // used in AsepriteAnimationFile and AsepriteManager
{
    int x;
    int y;
};

/* #region ---AsepriteAnimationFile class--- */

class AsepriteAnimationFile
{
    friend class
        AsepriteManager; // gives AsepriteManager access to private members of AsepriteAnimationFile. Used in createNewAnimFilePtr()
public:
    explicit AsepriteAnimationFile(const std::string& filename,
                                   Texture& texture,
                                   AsepriteManager& asepriteManager);

    ~AsepriteAnimationFile();

    FrameTag& getFrameTag(const std::string& filenameTagname) const;
    std::string getFilename() const;
    std::string getFilenameTagName() const;
    float getDurationCurrentFrame(int frameNumber) const;
    float getDurationCurrentFrame() const;
    int getSpriteSizeX() const;
    int getSpriteSizeY() const;
    bool hasAnimFinished() const;
    bool hasAnimFinishedPlusLastFrameDuration() const;
    int getCurrentFrame() const;
    int getMinFrame() const;
    int getMaxFrame() const;
    void setCurrentFrameToMinFrame();

    void setSpriteOffset(const std::string& AnimFileName, int x, int y);
    void setFrameTagOffset(const std::string& AnimFileTagname, int x, int y);
    void setFrameOffset(const std::string& AnimFileTagname, int frameNumber, int x, int y);
    void setLoop(const std::string& AnimFileTagname, bool loop);
    OffSets getSpriteOffset();
    OffSets getFrameTagOffset();
    OffSets getFrameOffset();
    bool getLoop() const;


    void drawFrame(const std::string& filenameTagname,
                   int x,
                   int y,
                   float scale = 1.0f,
                   Color color = WHITE,
                   bool flipX = false,
                   bool flipY = false);
    void drawCurrentSelectedTag(int x,
                                int y,
                                float scale = 1.0f,
                                Color color = WHITE,
                                bool flipX = false,
                                bool flipY = false) const;
    void resetBools();
    void update(float deltaTime);

    bool setFrameTag(const std::string& tagname);

private:
    // member variables
    std::string filename;             // filename, ex. "gbFighter", is also the name of the texture
    AsepriteManager* asepriteManager; // reference to the asepriteManager
    Texture texture;
    std::string current_filenameTagname;
    int current_frame_number; // current frame of the animation
    int min_frame;
    int max_frame;
    int spriteSizeX;
    int spriteSizeY;
    float update_counter;
    float current_duration;                             // duration of the current frame in milliseconds
    float animJustFinishedPlusLastFrameDurationCounter; // float value of duration of last frame
    bool animJustFinishedPlusLastFrameDurationCounterSet;
    bool animJustFinishedPlusLastFrameDuration;
    bool animJustFinished;
    bool loop;

    // data containers for offsets
    std::unordered_map<std::string, OffSets> spriteOffsets;                         // ("gbFighter", {10, 20})
    std::unordered_map<std::string, OffSets> frameTagOffsets;                       // "gbFighter-Punch", {10, 20}
    std::unordered_map<std::string, std::unordered_map<int, OffSets>> frameOffsets; // "gbFighter-Punch, 42, {10, 20}

    // intenal use only -> use data containers for setting offsets
    int spriteOffsetX;   // this will be applied for all frames of the animationFile (ex. all files of gbFighter)
    int spriteOffsetY;   // this will be applied for all frames of the animationFile (ex. all files of gbFighter)
    int frameTagOffsetX; // this will be applied only for all frames of specific frameTag (ex. only for gbFighter-Idle)
    int frameTagOffsetY; // this will be applied only for all frames of specific frameTag (ex. only for gbFighter-Idle)
    int frameOffsetX;    // this will be applied only for a specific frameNumber
    int frameOffsetY;    // this will be applied only for a specific frameNumber
    // -----------------------------------------------------------------------

    void nextFrame();

    void _drawFrame(const std::string& filenameTagname,
                    int frameNumber,
                    int sourceSpriteSizeX,
                    int sourceSpriteSizeY,
                    int x,
                    int y,
                    float scale,
                    Color color,
                    bool flipX,
                    bool flipY) const;
};

/* #endregion */

/* #region ---AsepriteManager class--- */
class AsepriteManager
{
public:
    // public methods
    explicit AsepriteManager(const std::string& foldername);
    ~AsepriteManager();

    void init();

    void loadAnimFile(const std::string& filename);

    FrameTag& getFrameTag(const std::string& filenameTagname);

    AsepriteAnimationFile* createNewAnimFilePtr(const std::string& initialFrameTag);

    Texture getTexture(const std::string& textureName);

    // public member variables
    unordered_map<std::string, FrameTag> frameTags; // all frameTags are stored here

    // data containers for offsets
    std::unordered_map<std::string, OffSets> spriteOffsets;                         // ("gbFighter", {10, 20})
    std::unordered_map<std::string, OffSets> frameTagOffsets;                       // "gbFighter-Punch", {10, 20}
    std::unordered_map<std::string, std::unordered_map<int, OffSets>> frameOffsets; // "gbFighter-Punch", 42, {10, 20}

private:
    // private methods
    nlohmann::json* loadJsonFile(const std::string& filename);

    // private member variable
    std::string foldername; // keeps the foldername, where all the json and png-files are located
    std::map<std::string, Texture> textures;
};
/* #endregion */

/* #region ---FrameTag struct--- */

struct FrameTag
{
    std::string tagname;
    std::string texturename;
    std::string filenameTagname;
    std::string direction;
    int sourceSizeX;
    int sourceSizeY;
    bool loop;
    int from;
    int to;
    unordered_map<int, int> frameNumberDuration;
};


#endif // GBFIGHTER_ASEPRITEMANAGER_H
