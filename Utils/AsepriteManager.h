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

    void _drawFrame(const std::string& filenameTagname,
                    int x,
                    int y,
                    float scale = 1.0f,
                    Color tint = WHITE,
                    bool flipX = false,
                    bool flipY = false,
                    int spriteOffsetX = 0,
                    int spriteOffsetY = 0);

public:
    explicit AsepriteAnimationFile(std::string filename,
                                   std::string foldername,
                                   Texture& texture,
                                   AsepriteManager& asepriteManager);

    ~AsepriteAnimationFile();

    // methods
    /**
     * @brief Get the Frame Tag object. The object has a name (for example "Idle"), a from, a to, a loop and a duration property. The number in "from"
     * is the position of the starting picture, the number in "to" is the last picture of the animation. After the last picture, the first picture (from)
     * hast to be played again.
     * @param tagname
     * @return FrameTag
     */
    FrameTag getFrameTag(const std::string& filenameTagname);
    std::string getAnimFilename() const;
    std::string getAnimFilenameTagname() const;
    float getDurationCurrentFrame(int frameNumber);
    float getDurationCurrentFrame();
    int getSpriteSizeX() const;
    int getSpriteSizeY() const;
    bool hasAnimJustFinished() const;
    bool hasAnimJustFinishedPlusLastFrameDuration() const;
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
    void drawCurrentSelectedTag(int x,
                                int y,
                                float scale,
                                Color tint,
                                bool flipX,
                                bool flipY,
                                int offsetFlippedX,
                                int offsetFlippedY);
    void resetBools();

    /**
     * @brief the update methode calls frequently the nextFrame() which switches to the next picture of the animation
     *
     * @param deltaTime
     */
    void update(float deltaTime);

    /**
     * @brief checks if the current_frame < max_frame and if so, switches to the next frame otherwise it goes back to the first frame of the animation
     *
     */
    void nextFrame();

    /**
     * @brief Set the Frame Tag object. If a invalid tagname is given, a runtime-error will be thrown. If the tagname is valid, the animation will be set to the first picture of the animation.
     * if the animation with the provided tag is already playing  the function returns false, otherwise it returns true.
     *
     * @param tagname
     * @return
     */
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

    void loadAnimFile(const std::string& filename);

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
    int spriteOffsetX;
    int spriteOffsetY;
    Dictionary<int, int> frameNumberDuration;
};

//overrite the operator<< for FrameTag
std::ostream& operator<<(std::ostream& os, const FrameTag& frameTag);
/* #endregion */

#endif // GBFIGHTER_ASEPRITEMANAGER_H
