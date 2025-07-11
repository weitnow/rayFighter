#include "AsepriteManager.h"


/* #region ---AsepriteAnimationFile Class */
AsepriteAnimationFile::AsepriteAnimationFile(std::string filename,
                                             std::string foldername,
                                             Texture& texture,
                                             AsepriteManager& asepriteManager)
{
    this->asepriteManager = &asepriteManager;
    this->filename = filename;
    this->texture = texture;
    current_filenameTagname = "none";
    current_frame = 0;
    min_frame = 0;
    max_frame = 0;
    spriteSizeX = 0;
    spriteSizeY = 0;
    update_counter = 0.0f;
    current_duration = 0.0f;
    animJustFinishedPlusLastFrameDurationCounter =
        20.0f; // needs to be higher than the duration of the last frame otherwise animJustFinishedPlusLastFrameDuration will be true immidiately
    animJustFinishedPlusLastFrameDurationCounterSet = false;
    animJustFinishedPlusLastFrameDuration = false;
    animJustFinished = false;
    loop = true;
    spriteOffsetX = 0; // this will be apllied for all frames of the animationFile (ex. all files of gbFighter)
    spriteOffsetY = 0; // this will be apllied for all frames of the animationFile (ex. all files of gbFighter)
    frameOffsetX = 0;  // this will be apllied only for all frames of specific frameTag (ex. only for gbFighter-Idle)
    frameOffsetY = 0;  // this will be apllied only for all frames of specific frameTag (ex. only for gbFighter-Idle)
}

AsepriteAnimationFile::~AsepriteAnimationFile()
{
}

FrameTag& AsepriteAnimationFile::getFrameTag(const std::string& filenameTagname) // for example "gbFighter-Idle"
{
    return this->asepriteManager->getFrameTag(filenameTagname);
}

std::string AsepriteAnimationFile::getAnimFilename() const
{
    return this->filename;
}

std::string AsepriteAnimationFile::getAnimFilenameTagname() const
{
    return this->current_filenameTagname;
}

float AsepriteAnimationFile::getDurationCurrentFrame(int frameNumber)
{
    int duration = this->asepriteManager->getFrameTag(current_filenameTagname).frameNumberDuration[this->current_frame];
    // 100 = 0.1 seconds
    return duration / 1000.0f;
}

float AsepriteAnimationFile::getDurationCurrentFrame()
{
    return getDurationCurrentFrame(current_frame);
}

int AsepriteAnimationFile::getSpriteSizeX() const
{
    return spriteSizeX;
}

int AsepriteAnimationFile::getSpriteSizeY() const
{
    return spriteSizeY;
}

bool AsepriteAnimationFile::hasAnimFinished() const
{
    return animJustFinished;
}

bool AsepriteAnimationFile::hasAnimFinishedPlusLastFrameDuration() const
{
    return animJustFinishedPlusLastFrameDuration;
}

int AsepriteAnimationFile::getCurrentFrame() const
{
    return current_frame;
}

int AsepriteAnimationFile::getMinFrame() const
{
    return min_frame;
}

int AsepriteAnimationFile::getMaxFrame() const
{
    return max_frame;
}

void AsepriteAnimationFile::setCurrentFrameToMinFrame()
{
    current_frame = min_frame;
}

void AsepriteAnimationFile::_drawFrame(const std::string& filenameTagname,
                                       int x,
                                       int y,
                                       float scale,
                                       Color tint,
                                       bool flipX,
                                       bool flipY)
{

    // Determine source rectangle (which part of the texture to draw)
    Rectangle sourceRec = {
        (float)current_frame * spriteSizeX,   // X position of the frame
        0,                                    // Y position (top of the texture)
        (flipX ? -1.0f : 1.0f) * spriteSizeX, // Flip horizontally if flipX is true
        (flipY ? -1.0f : 1.0f) * spriteSizeY  // Flip vertically if flipY is true
    };

    // Determine destination rectangle (where to draw the texture on screen)
    Rectangle destRec = {
        (float)x,            // X position to draw
        (float)y,            // Y position to draw
        spriteSizeX * scale, // Scaled width
        spriteSizeY * scale  // Scaled height
    };

    // Adjust the origin point for flipping
    Vector2 origin = {
        (flipX ? (spriteOffsetX + frameOffsetX)
               : -(spriteOffsetX + frameOffsetX)),                                 // Flip point adjusted by offsetFlipX
        (flipY ? (spriteOffsetY + frameOffsetY) : -(spriteOffsetY + frameOffsetY)) // Flip point adjusted by offsetFlipY
    };

    // Draw the texture with the specified scaling and tint
    DrawTexturePro(texture, sourceRec, destRec, origin, 0.0f, tint);
}

void AsepriteAnimationFile::drawFrame(const std::string& filenameTagname,
                                      int x,
                                      int y,
                                      float scale,
                                      Color tint,
                                      bool flipX,
                                      bool flipY)
{
    int sizeX = this->asepriteManager->getFrameTag(filenameTagname).sourceSizeX; // width of the frame
    int sizeY = this->asepriteManager->getFrameTag(filenameTagname).sourceSizeY; // height of the frame
    int frameNumber = this->asepriteManager->getFrameTag(filenameTagname).from;

    // Determine source rectangle (which part of the texture to draw)
    Rectangle sourceRec = {
        (float)frameNumber * sizeX,     // X position of the frame
        0,                              // Y position (top of the texture)
        (flipX ? -1.0f : 1.0f) * sizeX, // Flip horizontally if flipX is true
        (flipY ? -1.0f : 1.0f) * sizeY  // Flip vertically if flipY is true
    };

    // Determine destination rectangle (where to draw the texture on screen)
    Rectangle destRec = {
        (float)x,      // X position to draw
        (float)y,      // Y position to draw
        sizeX * scale, // Scaled width
        sizeY * scale  // Scaled height
    };

    // Draw the texture with the specified scaling and tint
    DrawTexturePro(texture, sourceRec, destRec, Vector2{0, 0}, 0.0f, tint);
}


void AsepriteAnimationFile::drawCurrentSelectedTag(int x, int y, float scale, Color tint)
{
    _drawFrame(current_filenameTagname, x, y, scale, tint, false, false);
}

void AsepriteAnimationFile::drawCurrentSelectedTag(int x, int y, float scale, Color tint, bool flipX, bool flipY)

{

    _drawFrame(current_filenameTagname, x, y, scale, tint, flipX, flipY);
}

void AsepriteAnimationFile::update(float deltaTime)
{
    // get the duration of the current frame
    current_duration = getDurationCurrentFrame(current_frame);
    // get the sprite size of the current frame
    spriteSizeX = this->asepriteManager->getFrameTag(current_filenameTagname).sourceSizeX;
    spriteSizeY = this->asepriteManager->getFrameTag(current_filenameTagname).sourceSizeY;

    // update the counter with the deltaTime
    update_counter += deltaTime;
    if (update_counter >= current_duration)
    {
        nextFrame();
        update_counter = 0.0f;
    }

    // if the animation just finished, count the time
    if (animJustFinishedPlusLastFrameDurationCounter > 0.0f)
    {

        animJustFinishedPlusLastFrameDurationCounter -= deltaTime;
        animJustFinishedPlusLastFrameDuration = false;
    }
    else
    {

        animJustFinishedPlusLastFrameDurationCounter = 0.0f;
        animJustFinishedPlusLastFrameDuration = true;
    }
}

void AsepriteAnimationFile::resetBools()
{
    animJustFinished = false;
    animJustFinishedPlusLastFrameDuration = false;
    animJustFinishedPlusLastFrameDurationCounter = 20.0f;
    animJustFinishedPlusLastFrameDurationCounterSet = false;
}

void AsepriteAnimationFile::nextFrame()
{
    // if the animation has only one frame
    if (max_frame - min_frame == 0)
    {
        if (!animJustFinishedPlusLastFrameDurationCounterSet)
        {
            animJustFinishedPlusLastFrameDurationCounter = getDurationCurrentFrame(current_frame) - 0.1f;
            animJustFinishedPlusLastFrameDurationCounterSet = true;
        }
    }
    // if the animation has more than one frame check if the current frame is not the last frame
    else if (current_frame < max_frame)
    {
        animJustFinished = false;
        current_frame++;
    }
    // if it is the last frame, check if the animation should loop
    else
    {
        // if the animation should loop, go back to the first frame
        if (loop)
            current_frame = min_frame;

        animJustFinished = true;
        animJustFinishedPlusLastFrameDurationCounter = getDurationCurrentFrame(current_frame) - 0.1f;
    }
}

bool AsepriteAnimationFile::setFrameTag(const std::string& filenameTagname)
{
    if (current_filenameTagname == filenameTagname)
    {
        return false;
    }

    current_filenameTagname = filenameTagname;

    if (this->asepriteManager->frameTags.find(filenameTagname) == this->asepriteManager->frameTags.end())
    {
        throw std::runtime_error(
            "AsepriteAnimationFile::setFrameTag -> Error: asepriteManager is nullptr or the filenameTagname " +
            filenameTagname + " does not exist");
    }

    resetBools();

    //set initial values
    FrameTag current_FrameTag = this->asepriteManager->getFrameTag(current_filenameTagname);
    min_frame = current_FrameTag.from;
    max_frame = current_FrameTag.to;
    spriteSizeX = current_FrameTag.sourceSizeX;
    spriteSizeY = current_FrameTag.sourceSizeY;
    loop = current_FrameTag.loop;
    spriteOffsetX = current_FrameTag.spriteOffsetX;
    spriteOffsetY = current_FrameTag.spriteOffsetY;
    frameOffsetX = current_FrameTag.frameOffsetX;
    frameOffsetY = current_FrameTag.frameOffsetY;


    if (this->filename != current_FrameTag.texturename)
    {
        this->texture = this->asepriteManager->getTexture(current_FrameTag.texturename);
        this->filename = current_FrameTag.texturename;
    }

    current_frame = min_frame;

    return true;
}


/* #endregion */

/* #region ---AsepriteManager class--- */

// foldername where the png and json-files are located
AsepriteManager::AsepriteManager(std::string foldername)
{
    this->foldername = foldername;
}

AsepriteManager::~AsepriteManager()
{
}
void AsepriteManager::init()
{
    // load all aseprite files in the folder

    // Spriteoffsets for the whole animationFile has to be set in loadAnimFile,
    // spriteOffsets for specific frames has to be set like this: getFrameTag("gbFighter-Punch").frameOffsetX = 5

    loadAnimFile("gbFighter", 0); // asepriteManager.frameTags[gbFighter-Idle] (0 is the spriteOffsetX)
                                  // asepriteManager.textures[gbFighter]


    getFrameTag("gbFighter-Punch").frameOffsetX = 6; // set the spriteOffsetX for the punch animation
    getFrameTag("gbFighter-DuckPunch").frameOffsetX = 6;
    getFrameTag("gbFighter-DuckBlock").frameOffsetX = -2;

    getFrameTag("gbFighter-Death").loop = false; // set loop to false for the death animation

    loadAnimFile("nesFighter", 6); // asepriteManager.frameTags[nesFighter-Idle] (6 is the spriteOffsetX)
                                   // asepriteManager.textures[nesFighter]

    getFrameTag("nesFighter-Death").loop = false; // set loop to false for the death animation


    loadAnimFile("barrel"); // asepriteManager.frameTags[barrel]
                            // asepriteManager.textures[barrel]

    loadAnimFile("stages"); // asepriteManager.frameTags[stage-temple]
                            // asepriteManager.textures[stage]

    loadAnimFile("thepit");

    loadAnimFile("bgUpperGui");
    getFrameTag("bgUpperGui-Amazed").loop = false;

    loadAnimFile("titleScreen");
    getFrameTag("titleScreen-Transition").loop = false;

    loadAnimFile("charSelectScreen");
    loadAnimFile("playerTags");

    loadAnimFile("stageSelectScreen");

    loadAnimFile("bgLowerGui");

    loadAnimFile("screenEffects");

    loadAnimFile("gbIntro");
    getFrameTag("gbIntro-Intro").loop = false;

    loadAnimFile("optionSelectScreen");
    getFrameTag("optionSelectScreen-Intro").loop = false;

    loadAnimFile("bg16SpriteCollection");

    loadAnimFile("gbSpear");
}

nlohmann::json* AsepriteManager::loadJsonFile(const std::string& filename)
{
    std::string path_with_filename = foldername + filename + ".json";
    std::ifstream i(path_with_filename);

    //allocate memory on the heap and store a new nlohmann::json-object and store a pointer to it
    //in the jsondata variable
    nlohmann::json* jsondata = new nlohmann::json();
    if (!i)
    {
        std::cerr << "Failed to open '" << path_with_filename << "'\n";
    }
    else
    {
        std::cout << path_with_filename << " successfully loaded\n";
        try
        {
            // load jsondata from file and put it into nLohmann::json jsondata
            i >> *jsondata;
        }
        catch (nlohmann::json::parse_error& e) //
        {
            std::cerr << "Failed to parse JSON: " << e.what() << "\n";
            delete jsondata;
            jsondata = nullptr;
        }
    }
    i.close();
    return jsondata;
}

void AsepriteManager::loadAnimFile(const std::string& filename, const int spriteOffsetX, const int spriteOffsetY)
{

    // --ADD FRAMETAG TO FRAMETAGS MEMBER VARIABLE--

    // loadJsonFile(filename) reads the jsonfile and returns a pointer to a nlohmann::json-object which
    // is on the heap. loadJsonFile will NOT be responsible for deleting memoy on the heap. thats why
    // we delete the jsonfile object on the heap at the end of this methode
    nlohmann::json* jsonfile = loadJsonFile(filename);

    // get how many frameTags are in the json
    int frameTagSize = (*jsonfile)["meta"]["frameTags"].size(); // 33 different frameTags (gbFighter.json)

    // get how many frames are in the json (there is always at least 1 frame)
    int frameSize = (*jsonfile)["frames"].size(); // 74 different frames (gbFighter.json)

    // Choose the correct frame key based on frameSize
    std::string frameKey = (frameSize == 1) ? (filename + ".aseprite") : (filename + " 0.aseprite");

    //create a new FrameTag object
    FrameTag frameTag;

    // check if file has frameTags
    if (frameTagSize > 0)
    {
        // file has frametags

        for (int i = 0; i < frameTagSize; ++i) // loop through frametags 0 bis 32
        {
            frameTag.frameNumberDuration.clear(); // Clear previous frame durations
            frameTag.tagname = (*jsonfile)["meta"]["frameTags"][i]["name"];
            frameTag.texturename = filename;
            frameTag.filenameTagname = filename + "-" + frameTag.tagname;
            frameTag.direction = (*jsonfile)["meta"]["frameTags"][i]["direction"];
            frameTag.sourceSizeX = (*jsonfile)["frames"][frameKey]["spriteSourceSize"]["w"];
            frameTag.sourceSizeY = (*jsonfile)["frames"][frameKey]["spriteSourceSize"]["h"];
            frameTag.loop = true;
            frameTag.from = (*jsonfile)["meta"]["frameTags"][i]["from"];
            frameTag.to = (*jsonfile)["meta"]["frameTags"][i]["to"];
            frameTag.frameOffsetX =
                0; // this will be apllied only for all frames of specific frameTag (ex. gbFighter-Idle)
            frameTag.frameOffsetY = 0;
            frameTag.spriteOffsetX = spriteOffsetX; // this will be apllied for all frames (ex. gbFighter)
            frameTag.spriteOffsetY = spriteOffsetY;

            // add the frameNumber and the duration of the frame to the frameNumberDuration map
            for (int j = frameTag.from; j <= frameTag.to; ++j)
            {
                if (frameSize == 1)
                {
                    frameTag.frameNumberDuration[j] = (*jsonfile)["frames"][frameKey]["duration"];
                }
                else
                {
                    frameTag.frameNumberDuration[j] =
                        (*jsonfile)["frames"][filename + " " + std::to_string(j) + ".aseprite"]["duration"];
                }
            }

            // adding it to the frameTags-Map, so its accessible like frameTags["gbFighter-Idle"], which would return the frameTag Idle of gbFighter.png
            frameTags[filename + "-" + frameTag.tagname] = frameTag;
        }
    }
    else
    {
        // file has NO frametags
        frameTag.frameNumberDuration.clear(); // Clear previous frame durations
        frameTag.tagname = filename;
        frameTag.texturename = filename;
        frameTag.filenameTagname = filename;
        frameTag.direction = "forward";
        frameTag.sourceSizeX = (*jsonfile)["frames"][frameKey]["spriteSourceSize"]["w"];
        frameTag.sourceSizeY = (*jsonfile)["frames"][frameKey]["spriteSourceSize"]["h"];
        frameTag.loop = false;
        frameTag.from = 0;
        frameTag.to = frameSize - 1;
        frameTag.frameOffsetX = 0; // this will be apllied only for all frames of specific frameTag (ex. gbFighter-Idle)
        frameTag.frameOffsetY = 0;
        frameTag.spriteOffsetX = 0; // this will be apllied for all frames (ex. gbFighter)
        frameTag.spriteOffsetY = 0;

        // add the frameNumber and the duration of the frame to the frameNumberDuration map
        for (int j = frameTag.from; j <= frameTag.to; ++j)
        {
            if (frameSize == 1)
            {
                frameTag.frameNumberDuration[j] = (*jsonfile)["frames"][frameKey]["duration"];
            }
            else
            {
                frameTag.frameNumberDuration[j] =
                    (*jsonfile)["frames"][filename + " " + std::to_string(j) + ".aseprite"]["duration"];
            }
        }

        // adding it to the frameTags-Map, so its accessible like frameTags["gbFighter-Idle"], which would return the frameTag Idle of gbFighter.png
        frameTags[filename] = frameTag;
    }

    delete jsonfile;

    // --ADD TEXTURE TO TEXTURES MEMEBER VARIABLE--
    textures[filename] = LoadTexture((foldername + filename + ".png").c_str());
}


FrameTag& AsepriteManager::getFrameTag(const std::string& filenameTagname)
{
    return frameTags.at(filenameTagname); // std::out_of_range will be thrown if key is missing
}

AsepriteAnimationFile* AsepriteManager::getAnimFile(const std::string& filename)
{
    auto it = this->textures.find(filename);
    if (it == this->textures.end())
    {
        throw std::runtime_error("Texture not found: " + filename);
    }
    return new AsepriteAnimationFile(filename, this->foldername, this->textures[filename], (*this));
}

Texture AsepriteManager::getTexture(const std::string& textureName)
{
    auto it = this->textures.find(textureName);
    if (it == this->textures.end())
    {
        throw std::runtime_error("Texture not found: " + textureName);
    }
    return this->textures[textureName];
}

/* #endregion */

/* #region ---FrameTag struct--- */
//overrite the operator<< for FrameTag - Implementation
std::ostream& operator<<(std::ostream& os, const FrameTag& frameTag)
{
    os << "Tagname: " << frameTag.tagname;
    os << ", \nTexturename: " << frameTag.texturename;
    os << ", \nFilenameTagname: " << frameTag.filenameTagname;
    os << " \nDirection: " << frameTag.direction;
    os << ", \nLoop: " << (frameTag.loop ? "yes" : "no");
    os << ", \nfrom: " << frameTag.from;
    os << ", \nto: " << frameTag.to << std::endl;
    return os;
}

/* #endregion */
