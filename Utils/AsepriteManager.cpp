#include "AsepriteManager.h"


/* #region ---AsepriteAnimationFile Class */
AsepriteAnimationFile::AsepriteAnimationFile(std::string filename, std::string foldername)
{
    this->filename = filename;
    texture = LoadTexture((foldername + filename + ".png").c_str());
    current_tag = "Idle";
    current_frame = 0;
    min_frame = getFrameTag(current_tag).from;
    max_frame = getFrameTag(current_tag).to;
    current_color = WHITE;
    current_scale = 1.0f;
    update_counter = 0.0f;
}

AsepriteAnimationFile::~AsepriteAnimationFile()
{
    std::cout << "Calling ~AsepriteAnimationFile() for " << filename << " and unloading its Texture." << std::endl;
    UnloadTexture(texture);
}

FrameTag AsepriteAnimationFile::getFrameTag(const std::string& tagname)
{
    for (auto& pair : frameTags)
    {
        if (pair.first == tagname)
        {
            return pair.second;
        }
    }
    // Return a default value if the tagname is not found
    FrameTag NoframeTagFound;
    NoframeTagFound.name = "noframetagfound";
    NoframeTagFound.from = 0;
    NoframeTagFound.to = 0;
    NoframeTagFound.loop = false;
    NoframeTagFound.duration = 0;
    return NoframeTagFound;
}

void AsepriteAnimationFile::drawFrame(const std::string& tagname, int x, int y, float scale, Color tint)
{
    // todo: implement scaling
    FrameTag frameTag = getFrameTag(tagname);
    DrawTextureRec(texture, {(float)current_frame * 32, 0, 32, (float)texture.height}, {(float)x, (float)y}, tint);
}

void AsepriteAnimationFile::drawCurrentSelectedTag(int x, int y)
{
    drawFrame(current_tag, x, y, this->current_scale, this->current_color);
}

void AsepriteAnimationFile::update(float deltaTime)
{
#ifdef DEBUG
    printFrameTag(current_tag);
#endif

    update_counter += deltaTime;
    if (update_counter >= 1.0f)
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

void AsepriteAnimationFile::setFrameTag(const std::string& tagname)
{
    if (current_tag == tagname)
    {
        return;
    }
    current_tag = tagname;
    min_frame = getFrameTag(current_tag).from;
    max_frame = getFrameTag(current_tag).to;
    current_frame = min_frame;
}

// debug-methods of AsepriteAnimationFile class
void AsepriteAnimationFile::printFrameTag(const std::string& tagname)
{
    if (!frameTagPrinted)
    {
        std::cout << "current tag: " << current_tag << std::endl;
        std::cout << frameTags[tagname] << std::endl;
    }
    frameTagPrinted = true;
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

/**
 * After loadAnimFile is executed the AsepriteManager animFiles-Obj of type maps
 * holds animFiles[gbFighter] = AnimationObject* AnimationObject has a frameTags
 * of type maps which holds frameTags[idle] = pair<from, to>
 * @param filename
 */
void AsepriteManager::loadAnimFile(const std::string& filename)
{
    // create a new AnimationObject on the heap and put a pointer to it into the map
    AsepriteAnimationFile* AnimObjPtr = new AsepriteAnimationFile(filename, this->foldername);
    animFiles[filename] = AnimObjPtr;

    // loadJsonFile(filename) reads the jsonfile and returns a pointer to a nlohmann::json-object which
    // is on the heap. loadJsonFile will NOT be responsible for deleting memoy on the heap.
    nlohmann::json* jsonfile = loadJsonFile(filename);

    // get how many frameTags are in the jsonfile and loop through them
    int frameTagSize = (*jsonfile)["meta"]["frameTags"].size();
    for (int i = 0; i < frameTagSize; ++i)
    {
        // create a FrameTag object and put it into the map
        FrameTag frameTag;
        frameTag.name = (*jsonfile)["meta"]["frameTags"][i]["name"];
        frameTag.from = (*jsonfile)["meta"]["frameTags"][i]["from"];
        frameTag.to = (*jsonfile)["meta"]["frameTags"][i]["to"];
        frameTag.direction = (*jsonfile)["meta"]["frameTags"][i]["direction"];
        frameTag.loop = false;
        frameTag.duration = 0;
        AnimObjPtr->frameTags[(*jsonfile)["meta"]["frameTags"][i]["name"]] = frameTag;
    }
    delete jsonfile;
}

void AsepriteManager::showLoadedAnimFiles()
{
    std::cout << "Loaded AsepriteAnimationFiles:\n";
    for (auto& pair : animFiles)
    {
        std::cout << "Filename: " << pair.first << ", AsepriteAnimationFile object address: " << pair.second
                  << std::endl;
    }
}


AsepriteAnimationFile* AsepriteManager::getAnimFile(const std::string& filename)
{
    // this returns a AsepriteAnimationFile*,
    // Todo: we have to make a copy and the return a pointer to the copy


    return animFiles[filename];
}

void AsepriteManager::UnloadRessources()
{
    std::cout
        << "Calling AsepriteManager::UnloadRessources() and deleting all AsepriteAnimationFile-Objects on the heap."
        << std::endl;
    for (auto& pair : animFiles)
    {
        std::cout << "animFiles[" << pair.first << "] = nullptr " << std::endl;
        delete pair.second;
        pair.second = nullptr;
    }
}
/* #endregion */

/* #region ---FrameTag struct--- */
//overrite the operator<< for FrameTag - Implementation
std::ostream& operator<<(std::ostream& os, const FrameTag& frameTag)
{
    os << "Tagname: " << frameTag.name << ", Direction: " << frameTag.direction;
    os << ", Loop: " << (frameTag.loop ? "yes" : "no");
    os << ", Duration: " << frameTag.duration << ", \nfrom: " << frameTag.from;
    os << ", \nto: " << frameTag.to << std::endl;
    return os;
}

/* #endregion */
