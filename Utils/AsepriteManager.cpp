#include "AsepriteManager.h"


/* #region ---AsepriteAnimationFile Class */
AsepriteAnimationFile2::AsepriteAnimationFile2(std::string filename,
                                               std::string foldername,
                                               Texture& texture,
                                               AsepriteManager& theManager)
{
    this->theManager = &theManager;
    this->filename = filename;
    this->texture = texture;
    current_tag = "Idle";
    current_frame = 0;
    min_frame = theManager.getFrameTag2("bla").from;
    max_frame = theManager.getFrameTag2("bla").to;
    current_color = WHITE;
    current_scale = 1.0f;
    update_counter = 0.0f;
}

AsepriteAnimationFile2::~AsepriteAnimationFile2()
{
}

FrameTag AsepriteAnimationFile2::getFrameTag(const std::string& tagname)
{
    AsepriteManager* Manager = this->theManager;
    theManager->getAnimFile("bla");
}

void AsepriteAnimationFile2::drawFrame(const std::string& tagname, int x, int y, float scale, Color tint)
{
    // todo: implement scaling
    FrameTag frameTag = this->theManager->getFrameTag2(tagname);
    DrawTextureRec(texture, {(float)current_frame * 32, 0, 32, (float)texture.height}, {(float)x, (float)y}, tint);
}

void AsepriteAnimationFile2::drawCurrentSelectedTag(int x, int y)
{
    drawFrame(current_tag, x, y, this->current_scale, this->current_color);
}

void AsepriteAnimationFile2::update(float deltaTime)
{

    update_counter += deltaTime;
    if (update_counter >= 1.0f)
    {
        nextFrame();
        update_counter = 0.0f;
    }
}

void AsepriteAnimationFile2::nextFrame()
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

void AsepriteAnimationFile2::setFrameTag(const std::string& tagname)
{
    if (current_tag == tagname)
    {
        return;
    }
    current_tag = tagname;
    min_frame = this->theManager->getFrameTag2(current_tag).from;
    max_frame = this->theManager->getFrameTag2(current_tag).to;
    current_frame = min_frame;
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

    // --ADD FRAMETAG TO FRAMETAGS MEMBER VARIABLE--

    // loadJsonFile(filename) reads the jsonfile and returns a pointer to a nlohmann::json-object which
    // is on the heap. loadJsonFile will NOT be responsible for deleting memoy on the heap. thats why
    // we delete the jsonfile object on the heap at the end of this methode
    nlohmann::json* jsonfile = loadJsonFile(filename);

    // get how many frameTags are in the jsonf#ifdef DEBUG
    // prints all information about the current selected tag (tagname, direction, loop, from, to)

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
        frameTag.texturename = filename;

        // adding it to the frameTags-Map, so its accessible like frameTags["gbFighter-Idle"], which would return the frameTag Idle of gbFighter.png
        frameTags[filename + "-" + frameTag.name] = frameTag;
    }
    delete jsonfile;

    // --ADD TEXTURE TO TEXTURES MEMEBER VARIABLE--
    textures[filename] = LoadTexture((foldername + filename + ".png").c_str());
}


FrameTag AsepriteManager::getFrameTag2(const std::string& tagname)
{
    return frameTags["gbFighter-Idle"]; // todo: get rid of the hardcoded tagname
}


AsepriteAnimationFile2* AsepriteManager::getAnimFile(const std::string& filename)
{
    // this returns a AsepriteAnimationFile2*,
    // Todo: generate a AsepriteAnimationFile2* and return it

    AsepriteAnimationFile2* newAsepriteAnimationFile2;
    newAsepriteAnimationFile2 = new AsepriteAnimationFile2(filename, this->foldername, this->textures[filename], *this);
    return newAsepriteAnimationFile2;
    //return new AsepriteAnimationFile2(filename, this->foldername, this->textures[filename], *this);
}

void AsepriteManager::UnloadRessources()
{
    //Todo: Implement Unloading Ressources
    /*
    std::cout
        << "Calling AsepriteManager::UnloadRessources() and deleting all AsepriteAnimationFile-Objects on the heap."
        << std::endl;
    for (auto& pair : animFiles)
    {
        std::cout << "animFiles[" << pair.first << "] = nullptr " << std::endl;
        delete pair.second;
        pair.second = nullptr;
    }
    */
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
