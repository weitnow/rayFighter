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

/* #region ---AsepriteAnimationFile class--- */

/**
 * @brief currently holds filename "gbfighter", and its texture, as well as a frameTags<string, FrameTag>
 * @param filename Filename as a String without file-extension. The class will look for a [filename].png and [filename].json
 * @param foldername Foldername where the png and json is located
 */
class AsepriteAnimationFile
{
private:
    // member variables
    std::string filename;             // filename, ex. "gbFighter", is also the name of the texture
    AsepriteManager* asepriteManager; // reference to the asepriteManager
    Texture texture;
    std::string current_filenameTagname;
    int current_frame; // current frame of the animation
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
    int spriteOffsetX; // this will be applied for all frames of the animationFile (stored in FrameTag object in every frame)
    int spriteOffsetY; // this will be applied for all frames of the animationFile (stored in FrameTag object in every frame)
    int frameOffsetX; // this will be applied only for all frames of specific frameTag (stored in FrameTag object in specific frame)
    int frameOffsetY; // this will be applied only for all frames of specific frameTag (stored in FrameTag object in specific frame)

    void nextFrame();
    void _drawFrame(const std::string& filenameTagname,
                    int x,
                    int y,
                    float scale = 1.0f,
                    Color tint = WHITE,
                    bool flipX = false,
                    bool flipY = false);

public:
    explicit AsepriteAnimationFile(std::string filename,
                                   std::string foldername,
                                   Texture& texture,
                                   AsepriteManager& asepriteManager);

    ~AsepriteAnimationFile();

    FrameTag& getFrameTag(const std::string& filenameTagname);
    std::string getAnimFilename() const;
    std::string getAnimFilenameTagname() const;
    float getDurationCurrentFrame(int frameNumber);
    float getDurationCurrentFrame();
    int getSpriteSizeX() const;
    int getSpriteSizeY() const;
    bool hasAnimFinished() const;
    bool hasAnimFinishedPlusLastFrameDuration() const;
    int getCurrentFrame() const;
    int getMinFrame() const;
    int getMaxFrame() const;
    void setCurrentFrameToMinFrame();

    void drawFrame(const std::string& filenameTagname,
                   int x,
                   int y,
                   float scale = 1.0f,
                   Color tint = WHITE,
                   bool flipX = false,
                   bool flipY = false);
    void drawCurrentSelectedTag(int x, int y, float scale = 1.0f, Color tint = WHITE);
    void drawCurrentSelectedTag(int x, int y, float scale, Color tint, bool flipX, bool flipY);
    void resetBools();
    void update(float deltaTime);

    bool setFrameTag(const std::string& tagname);
};

/* #endregion */

/* #region ---AsepriteManager class--- */
/**
 * @class AsepriteManager
 * @brief The object instantiated of this class controlls the loading of sprites
 * @param[in] foldername where the png and json-files of the aseprite-assets are located
 */
class AsepriteManager
{
public:
    // public methods
    explicit AsepriteManager(std::string foldername);
    ~AsepriteManager();

    void init();

    void loadAnimFile(const std::string& filename, const int spriteOffsetX = 0, const int spriteOffsetY = 0);

    FrameTag& getFrameTag(const std::string& filenameTagname);

    AsepriteAnimationFile* getAnimFile(const std::string& filename);

    Texture getTexture(const std::string& textureName);

    // public member variables
    Dictionary<std::string, FrameTag> frameTags;

private:
    // private methods
    /**
     * @brief This function reads a JsonFile, creates a nlohmann:json-object on the heap and returns a pointer to this json-object.
     * it does NOT handle the deletion of this object on the heap. this needs to be done through the code which calls the method loadJsonFile
     * an receives the pointer to the object on the heap.
     * @param filename filename of a .json-object without .json at the end
     * @return nlohmann::json* : A pointer to a json-object
     */
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
    // Todo: get rid of spriteOffsetX and spriteOffsetY
    int frameOffsetX; // this will be apllied only for all frames of specific frameTag (ex. gbFighter-Idle)
    int frameOffsetY;
    int spriteOffsetX; // this will be apllied for all frames (ex. gbFighter)
    int spriteOffsetY;
    Dictionary<int, int> frameNumberDuration;
};

//overrite the operator<< for FrameTag
std::ostream& operator<<(std::ostream& os, const FrameTag& frameTag);
/* #endregion */

#endif // GBFIGHTER_ASEPRITEMANAGER_H
