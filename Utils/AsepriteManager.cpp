#include "AsepriteManager.h"


/* #region ---AsepriteAnimationFile Class */
AsepriteAnimationFile::AsepriteAnimationFile(const std::string& filename,
                                             Texture& texture,
                                             AsepriteManager& asepriteManager)
{
    this->asepriteManager = &asepriteManager;
    this->filename = filename;
    this->texture = texture;
    current_filenameTagname = "none";
    current_frame_number = 0;
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
    spriteOffsetX = 0;   // this will be applied for all frames of the animationFile (ex. all files of gbFighter)
    spriteOffsetY = 0;   // this will be applied for all frames of the animationFile (ex. all files of gbFighter)
    frameTagOffsetX = 0; // this will be applied only for all frames of specific frameTag (ex. only for gbFighter-Idle)
    frameTagOffsetY = 0; // this will be applied only for all frames of specific frameTag (ex. only for gbFighter-Idle)
    frameOffsetX = 0;    // this will be applied only for a specific frameNumber
    frameOffsetY = 0;    // this will be applied only for a specific frameNumber
}

AsepriteAnimationFile::~AsepriteAnimationFile()
{
}

FrameTag& AsepriteAnimationFile::getFrameTag(const std::string& filenameTagname) const // for example "gbFighter-Idle"
{
    return this->asepriteManager->getFrameTag(filenameTagname);
}

std::string AsepriteAnimationFile::getFilename() const
{
    return this->filename;
}

std::string AsepriteAnimationFile::getFilenameTagName() const
{
    return this->current_filenameTagname;
}

float AsepriteAnimationFile::getDurationCurrentFrame(int frameNumber) const
{
    int duration = this->asepriteManager->getFrameTag(current_filenameTagname).frameNumberDuration[this->current_frame_number];
    // 100 = 0.1 seconds
    return duration / 1000.0f;
}

float AsepriteAnimationFile::getDurationCurrentFrame() const
{
    return getDurationCurrentFrame(current_frame_number);
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
    return current_frame_number;
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
    current_frame_number = min_frame;
}
void AsepriteAnimationFile::setSpriteOffset(const std::string& AnimFileName, int x, int y)
{
    // Todo: Implement it
}
void AsepriteAnimationFile::setFrameTagOffset(const std::string& AnimFileTagname, int x, int y)
{
    // Todo: Implement it
}
void AsepriteAnimationFile::setFrameOffset(const std::string& AnimFileTagname, int frameNumber, int x, int y)
{
    // Todo: Implement it
}
void AsepriteAnimationFile::setLoop(const std::string& AnimFileTagname, bool loop)
{
    // Todo: Implement it
}
OffSets AsepriteAnimationFile::getSpriteOffset()
{
    auto it = spriteOffsets.find(filename);
    return (it != spriteOffsets.end()) ? it->second : OffSets{0, 0};
}
OffSets AsepriteAnimationFile::getFrameTagOffset()
{
    auto it = frameTagOffsets.find(current_filenameTagname);
    return (it != frameTagOffsets.end()) ? it->second : OffSets{0, 0};
}
OffSets AsepriteAnimationFile::getFrameOffset()
{
    auto tagIt = frameOffsets.find(current_filenameTagname);
    if (tagIt != frameOffsets.end())
    {
        auto frameIt = tagIt->second.find(current_frame_number);
        if (frameIt != tagIt->second.end())
        {
            return frameIt->second;
        }
    }
    return OffSets{0, 0};
}
bool AsepriteAnimationFile::getLoop() const
{
    // Todo: Implement it
    return false;
}

void AsepriteAnimationFile::_drawFrame(const std::string& filenameTagname,
                                       int frameNumber,
                                       int sourceSpriteSizeX,
                                       int sourceSpriteSizeY,
                                       int x,
                                       int y,
                                       float scale,
                                       Color color,
                                       bool flipX,
                                       bool flipY) const
{

    // Determine source rectangle (which part of the texture to draw)
    Rectangle sourceRec = {
        (float)frameNumber * sourceSpriteSizeX,   // X position of the frame
        0,                                    // Y position (top of the texture)
        (flipX ? -1.0f : 1.0f) * sourceSpriteSizeX, // Flip horizontally if flipX is true
        (flipY ? -1.0f : 1.0f) * sourceSpriteSizeY  // Flip vertically if flipY is true
    };

    // Determine destination rectangle (where to draw the texture on screen)
    // Position + offset
    Rectangle destRec = {static_cast<float>(x + spriteOffsetX + frameTagOffsetX + frameOffsetX),
                         static_cast<float>(y + spriteOffsetY + frameTagOffsetY + frameOffsetY),
                         sourceSpriteSizeX * scale,
                         sourceSpriteSizeY * scale};

    Vector2 origin = {0, 0};

    // Draw the texture with the specified scaling and tint
    DrawTexturePro(texture, sourceRec, destRec, origin, 0.0f, color);

    // Draw the Spriteborder
    if (Global::debugSpriteBorder)
    {
        DrawRectangleLinesEx(destRec, 1.f, YELLOW);
    }
}

void AsepriteAnimationFile::drawFrame(const std::string& filenameTagname,
                                      int x,
                                      int y,
                                      float scale,
                                      Color color,
                                      bool flipX,
                                      bool flipY)
{

    int sizeX = this->asepriteManager->getFrameTag(filenameTagname).sourceSizeX; // width of the frame
    int sizeY = this->asepriteManager->getFrameTag(filenameTagname).sourceSizeY; // height of the frame
    int frameNumber = this->asepriteManager->getFrameTag(filenameTagname).from;

    _drawFrame(filenameTagname, frameNumber, sizeX, sizeY, x, y, scale, color, flipX, flipY);

}

void AsepriteAnimationFile::drawCurrentSelectedTag(int x, int y, float scale, Color color, bool flipX, bool flipY) const

{
    _drawFrame(current_filenameTagname, current_frame_number, spriteSizeX, spriteSizeY, x, y, scale, color, flipX, flipY);
}

void AsepriteAnimationFile::update(float deltaTime)
{


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
            animJustFinishedPlusLastFrameDurationCounter = getDurationCurrentFrame(current_frame_number) - 0.1f;
            animJustFinishedPlusLastFrameDurationCounterSet = true;
        }
    }
    // if the animation has more than one frame check if the current frame is not the last frame
    else if (current_frame_number < max_frame)
    {
        animJustFinished = false;
        current_frame_number++;
    }
    // if it is the last frame, check if the animation should loop
    else
    {
        // if the animation should loop, go back to the first frame
        if (loop)
            current_frame_number = min_frame;

        animJustFinished = true;
        animJustFinishedPlusLastFrameDurationCounter = getDurationCurrentFrame(current_frame_number) - 0.1f;
    }

    // update current_duration and spritesize
    // get the duration of the current frame
    current_duration = getDurationCurrentFrame(current_frame_number);
    // get the sprite size of the current frame
    spriteSizeX = this->asepriteManager->getFrameTag(current_filenameTagname).sourceSizeX;
    spriteSizeY = this->asepriteManager->getFrameTag(current_filenameTagname).sourceSizeY;

    // update offsets
    spriteOffsetX = getSpriteOffset().x;
    spriteOffsetY = getSpriteOffset().y;
    frameTagOffsetX = getFrameTagOffset().x;
    frameTagOffsetY = getFrameTagOffset().y;
    frameOffsetX = getFrameOffset().x;
    frameOffsetY = getFrameOffset().y;
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
    const FrameTag& current_FrameTag = this->asepriteManager->getFrameTag(current_filenameTagname);
    min_frame = current_FrameTag.from;
    max_frame = current_FrameTag.to;
    spriteSizeX = current_FrameTag.sourceSizeX;
    spriteSizeY = current_FrameTag.sourceSizeY;
    loop = current_FrameTag.loop;
    spriteOffsetX = getSpriteOffset().x;
    spriteOffsetY = getSpriteOffset().y;
    frameTagOffsetX = getFrameTagOffset().x;
    frameTagOffsetY = getFrameTagOffset().y;
    frameOffsetX = getFrameOffset().x;
    frameOffsetY = getFrameOffset().y;
    current_duration = getDurationCurrentFrame(current_frame_number);

    if (this->filename != current_FrameTag.texturename)
    {
        this->texture = this->asepriteManager->getTexture(current_FrameTag.texturename);
        this->filename = current_FrameTag.texturename;
    }

    current_frame_number = min_frame;

    return true;
}


/* #endregion */

/* #region ---AsepriteManager class--- */

// foldername where the png and json-files are located
AsepriteManager::AsepriteManager(const std::string& foldername)
{
    this->foldername = foldername;
}

AsepriteManager::~AsepriteManager()
{
}
void AsepriteManager::init()
{

    // set offsets, needs to be done before loadAnimFile!
    spriteOffsets["gbFighter"] = {0, 0};
    frameTagOffsets["gbFighter-Punch"] = {6, 0};
    frameTagOffsets["gbFighter-DuckPunch"] = {6, 0};
    frameTagOffsets["gbFighter-DuckBlock"] = {-2, 0};
    frameOffsets["gbFighter-Punch"][43] = {5, 0};

    spriteOffsets["nesFighter"] = {6, 0};

    loadAnimFile("gbFighter");

    loadAnimFile("debugFighter"); //Todo: get rid of this


    getFrameTag("gbFighter-Death").loop = false; // set loop to false for the death animation

    loadAnimFile("nesFighter"); // asepriteManager.frameTags[nesFighter-Idle] (6 is the spriteOffsetX)
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

    loadAnimFile("debug32");
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
    // this method reads jsonfile, generates a frametag-object for each frameTag and loads the correct texture (png) file and stores it in the std::map<string, texture>

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

            for (int j = frameTag.from; j <= frameTag.to; ++j)
            {
                // add the frameNumber and the duration of the frame to the frameNumberDuration map
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

AsepriteAnimationFile* AsepriteManager::createNewAnimFilePtr(const std::string& initialFrameTag)
{
    const FrameTag* frameTagPtr = nullptr;
    std::string textureName;

    // Check if frameTag exists
    auto frameTagIt = this->frameTags.find(initialFrameTag);
    if (frameTagIt != this->frameTags.end()) {
        frameTagPtr = &frameTagIt->second;
        textureName = frameTagPtr->texturename;
    } else
    {
        //throw std::runtime_error("No FrameTag found with Name: " + initialFrameTag);
    }


    //Create animation file
    auto* newAnimFile = new AsepriteAnimationFile(textureName, this->textures[textureName], (*this));

    // only set frameTag name if an actual FrameTag was found
    if (frameTagPtr != nullptr) {
        newAnimFile->setFrameTag(initialFrameTag);
    }

    // Deep copy maps
    newAnimFile->spriteOffsets     = this->spriteOffsets;
    newAnimFile->frameTagOffsets   = this->frameTagOffsets;
    newAnimFile->frameOffsets      = this->frameOffsets;

    return newAnimFile;
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
