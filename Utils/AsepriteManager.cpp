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
}

AsepriteAnimationFile::~AsepriteAnimationFile()
{
}

FrameTag AsepriteAnimationFile::getFrameTag(const std::string& filenameTagname) // for example "gbFighter-Idle"
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

bool AsepriteAnimationFile::hasAnimJustFinished() const
{
    return animJustFinished;
}

bool AsepriteAnimationFile::hasAnimJustFinishedPlusLastFrameDuration() const
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

void AsepriteAnimationFile::_drawFrame(const std::string& filenameTagname,
                                       int x,
                                       int y,
                                       float scale,
                                       Color tint,
                                       bool flipX,
                                       bool flipY,
                                       int offsetFlipX)
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
        (flipX ? offsetFlipX : -offsetFlipX), // Flip point adjusted by offsetFlipX
        0                                     // Y origin point remains unchanged
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
    _drawFrame(current_filenameTagname, x, y, scale, tint, false, false, 0);
}

void AsepriteAnimationFile::drawCurrentSelectedTag(int x,
                                                   int y,
                                                   float scale,
                                                   Color tint,
                                                   bool flipX,
                                                   bool flipY,
                                                   int offsetFlippedX)
{
    _drawFrame(current_filenameTagname, x, y, scale, tint, flipX, flipY, offsetFlippedX);
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
    animJustFinished = false;

    FrameTag current_FrameTag = this->asepriteManager->getFrameTag(current_filenameTagname);

    min_frame = current_FrameTag.from;
    max_frame = current_FrameTag.to;
    spriteSizeX = current_FrameTag.sourceSizeX;
    spriteSizeY = current_FrameTag.sourceSizeY;
    loop = current_FrameTag.loop;

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
    loadAnimFile("gbFighter"); // asepriteManager.frameTags[gbFighter-Idle]
                               // asepriteManager.textures[gbFighter]

    getFrameTag("gbFighter-Death").loop = false; // set loop to false for the death animation


    loadAnimFile("nesFighter"); // asepriteManager.frameTags[nesFighter-Idle]
                                // asepriteManager.textures[nesFighter]

    getFrameTag("nesFighter-Death").loop = false; // set loop to false for the death animation

    loadAnimFile("bgAnimation"); // asepriteManager.frameTags[bgAnimation]
                                 // asepriteManager.textures[bgAnimation]

    loadAnimFile("barrel"); // asepriteManager.frameTags[barrel]
                            // asepriteManager.textures[barrel]

    loadAnimFile("stage"); // asepriteManager.frameTags[stage-temple]
                           // asepriteManager.textures[stage]

    loadAnimFile("deadSkull");
    loadAnimFile("titleScreen");
    getFrameTag("titleScreen-Transition").loop = false;
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

void AsepriteManager::loadAnimFile(const std::string& filename)
{

    // --ADD FRAMETAG TO FRAMETAGS MEMBER VARIABLE--

    // loadJsonFile(filename) reads the jsonfile and returns a pointer to a nlohmann::json-object which
    // is on the heap. loadJsonFile will NOT be responsible for deleting memoy on the heap. thats why
    // we delete the jsonfile object on the heap at the end of this methode
    nlohmann::json* jsonfile = loadJsonFile(filename);

    // get how many frameTags are in the json
    int frameTagSize = (*jsonfile)["meta"]["frameTags"].size();

    // get how many frames are in the json
    int frameSize = (*jsonfile)["frames"].size();

    // check if the file has frames
    if (frameSize == 0)
    {
        std::cerr << "Error: File " << filename << " has no frames" << std::endl;
        return;
    }

    // if there are at least one frame, generate the FrameTag Obj
    FrameTag frameTag;

    // check if file has frameTags
    if (frameTagSize > 0)
    {
        // file has frametags

        for (int i = 0; i < frameTagSize; ++i)
        {
            frameTag.tagname = (*jsonfile)["meta"]["frameTags"][i]["name"];
            frameTag.texturename = filename;
            frameTag.filenameTagname = filename + "-" + frameTag.tagname;
            frameTag.direction = (*jsonfile)["meta"]["frameTags"][i]["direction"];
            frameTag.sourceSizeX = (*jsonfile)["frames"][filename + " 0.aseprite"]["spriteSourceSize"]["w"];
            frameTag.sourceSizeY = (*jsonfile)["frames"][filename + " 0.aseprite"]["spriteSourceSize"]["h"];
            frameTag.loop = true;
            frameTag.from = (*jsonfile)["meta"]["frameTags"][i]["from"];
            frameTag.to = (*jsonfile)["meta"]["frameTags"][i]["to"];

            // add the frameNumber and the duration of the frame to the frameNumberDuration map
            for (int j = frameTag.from; j <= frameTag.to; ++j)
            {
                frameTag.frameNumberDuration[j] =
                    (*jsonfile)["frames"][filename + " " + std::to_string(j) + ".aseprite"]["duration"];
            }

            // adding it to the frameTags-Map, so its accessible like frameTags["gbFighter-Idle"], which would return the frameTag Idle of gbFighter.png
            frameTags[filename + "-" + frameTag.tagname] = frameTag;
        }
    }
    else
    {
        // file has NO frametags

        frameTag.tagname = filename;
        frameTag.texturename = filename;
        frameTag.filenameTagname = filename;
        frameTag.from = 0;
        frameTag.to = frameSize - 1;
        frameTag.direction = "forward";
        frameTag.loop = false;
        frameTag.sourceSizeX = (*jsonfile)["frames"][filename + " 0.aseprite"]["spriteSourceSize"]["w"];
        frameTag.sourceSizeY = (*jsonfile)["frames"][filename + " 0.aseprite"]["spriteSourceSize"]["h"];

        // add the frameNumber and the duration of the frame to the frameNumberDuration map
        for (int j = frameTag.from; j <= frameTag.to; ++j)
        {
            frameTag.frameNumberDuration[j] =
                (*jsonfile)["frames"][filename + " " + std::to_string(j) + ".aseprite"]["duration"];
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
    try
    {
        return frameTags.at(filenameTagname); // for example frameTags["gbFighter-Idle"]
    }
    catch (const std::out_of_range& e)
    {
        std::cerr << "AsepriteManager::getFrameTag -> Error: FrameTag " << filenameTagname << " does not exist"
                  << std::endl;
    }
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
