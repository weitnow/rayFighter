//
// Created by weitnow on 12/16/23.
//
#include "AsepriteManager.h"

// foldername where the png and json-files are located
AsepriteManager::AsepriteManager(std::string foldername)
{
    this->foldername = foldername;
}

AsepriteManager::~AsepriteManager()
{
}

/**
 * @brief This function loads a JsonFile and return a pointer to a json-object
 * @param filename filename of a .json-object without .json at the end
 * @return nlohmann::json* : A pointer to a json-object
 */
nlohmann::json *AsepriteManager::loadJsonFile(const std::string &filename)
{
    std::string path_with_filename = foldername + filename + ".json";
    std::ifstream i(path_with_filename);
    nlohmann::json *jsondata = new nlohmann::json();
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
        catch (nlohmann::json::parse_error &e)
        {
            std::cerr << "Failed to parse JSON: " << e.what() << "\n";
            delete jsondata;
        }
    }
    i.close();
    return jsondata;
}

/**
 * After loadAnimFile is executed the AsepriteManager animFiles-Obj of type maps holds
 * animFiles[gbFighter] = AnimationObject*
 * AnimationObject has a frameTags of type maps which holds frameTags[idle] = pair<from, to>
 * @param filename
 */
void AsepriteManager::loadAnimFile(const std::string &filename)
{
    // create a new AnimationObject and put it into the map
    AsepriteAnimationFile *AnimObjPtr = new AsepriteAnimationFile(filename, this->foldername);
    animFiles[filename] = AnimObjPtr;

    // create a jsonfile-ptr and load the jsonfile
    nlohmann::json *jsonfile = loadJsonFile(filename);

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
    for (auto &pair : animFiles)
    {
        std::cout << "Filename: " << pair.first << ", AsepriteAnimationFile object address: " << pair.second << std::endl;
    }
}

/**
 * @brief This function returns a pointer to an AnimationObject
 * @param filename filename of a .json-object without .json at the end
 * @return AnimationObject* : A pointer to an AnimationObject
 *
 * the AnimationObject has a frameTags of type maps which holds frameTags["Animation Name as String"] = pair<from, to>
 */
AsepriteAnimationFile *AsepriteManager::getAnimFile(const std::string &filename)
{

    return animFiles[filename];
}

void AsepriteManager::UnloadRessources()
{
    // delete all pointers and clear memory
    for (auto &pair : animFiles)
    {
        delete pair.second;
        pair.second = nullptr;
    }
}

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
    float update_counter = 0.0f;
}

AsepriteAnimationFile::~AsepriteAnimationFile()
{
    std::cout << "Unloading AsepriteAnimationFile " << filename << " at adress " << this << std::endl;
    UnloadTexture(texture);
}

FrameTag AsepriteAnimationFile::getFrameTag(const std::string &tagname)
{
    for (auto &pair : frameTags)
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

void AsepriteAnimationFile::drawFrame(const std::string &tagname, int x, int y, float scale, Color tint)
{
    // todo: implement scale
    FrameTag frameTag = getFrameTag(tagname);
    DrawTextureRec(texture, {(float)current_frame * 32, 0, 32, (float)texture.height}, {(float)x, (float)y}, tint);
}

void AsepriteAnimationFile::drawCurrentSelectedTag(int x, int y)
{
    drawFrame(current_tag, x, y, this->current_scale, this->current_color);
}

void AsepriteAnimationFile::update(float deltaTime)
{
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

void AsepriteAnimationFile::setFrameTag(const std::string &tagname)
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
