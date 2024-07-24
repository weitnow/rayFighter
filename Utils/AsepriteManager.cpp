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
    current_color = WHITE;
    current_scale = 1.0f;
    update_counter = 0.0f;
}

AsepriteAnimationFile::~AsepriteAnimationFile()
{
}

FrameTag AsepriteAnimationFile::getFrameTag(const std::string& filenameTagname) // for example "gbFighter-Idle"
{
    return this->asepriteManager->getFrameTag(filenameTagname);
}

float AsepriteAnimationFile::getDurationCurrentFrame(int frameNumber)
{
    int duration = this->asepriteManager->getFrameTag(current_filenameTagname).frameNumberDuration[this->current_frame];
    // 100 = 0.1 seconds
    return duration / 1000.0f;
}

void AsepriteAnimationFile::drawFrame(const std::string& filenameTagname, int x, int y, float scale, Color tint)
{
    // todo: implement scaling
    int sizeX = this->asepriteManager->getFrameTag(filenameTagname).sourceSizeX;
    int sizeY = this->asepriteManager->getFrameTag(filenameTagname).sourceSizeY;
    DrawTextureRec(texture,
                   {(float)current_frame * sizeX, 0, float(sizeY), (float)texture.height},
                   {(float)x, (float)y},
                   tint);
}

void AsepriteAnimationFile::drawCurrentSelectedTag(int x, int y)
{
    drawFrame(current_filenameTagname, x, y, this->current_scale, this->current_color);
}

void AsepriteAnimationFile::update(float deltaTime)
{
    // get the duration of the current frame
    current_duration = getDurationCurrentFrame(current_frame);

    // update the counter with the deltaTime
    update_counter += deltaTime;
    if (update_counter >= current_duration)
    {
        nextFrame();
        update_counter = 0.0f;
    }
}

void AsepriteAnimationFile::nextFrame()
{
    if (current_frame < max_frame)
    {
        current_frame++;
    }
    else
    {
        current_frame = min_frame;
    }
}

bool AsepriteAnimationFile::setFrameTag(const std::string& filenameTagname)
{
    if (current_filenameTagname == filenameTagname)
    {
        return false;
    }


    if (this->asepriteManager->frameTags.find(filenameTagname) == this->asepriteManager->frameTags.end())
    {
        throw std::runtime_error("AsepriteAnimationFile::setFrameTag -> Error: asepriteManager is nullptr");
    }

    current_filenameTagname = filenameTagname;

    FrameTag current_FrameTag = this->asepriteManager->getFrameTag(current_filenameTagname);

    min_frame = current_FrameTag.from;
    max_frame = current_FrameTag.to;

    if (this->filename != current_FrameTag.texturename)
    {
        this->texture = this->asepriteManager->getTexture(current_FrameTag.texturename);
        //std::cout << filename << " != " << current_FrameTag.texturename << std::endl;
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
            frameTag.loop = false;
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


FrameTag AsepriteManager::getFrameTag(const std::string& filenameTagname)
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
