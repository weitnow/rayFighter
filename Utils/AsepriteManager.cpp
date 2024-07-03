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
    current_tag = "Idle";
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

void AsepriteAnimationFile::drawFrame(const std::string& tagname, int x, int y, float scale, Color tint)
{
    // todo: implement scaling
    FrameTag frameTag = this->asepriteManager->getFrameTag(tagname);
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

void AsepriteAnimationFile::setFrameTag(const std::string& tagname)
{
    if (current_tag == tagname)
    {
        return;
    }
    current_tag = tagname;
    min_frame = this->asepriteManager->getFrameTag(current_tag).from;
    max_frame = this->asepriteManager->getFrameTag(current_tag).to;
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

void AsepriteManager::loadAnimFile(const std::string& filename)
{

    // --ADD FRAMETAG TO FRAMETAGS MEMBER VARIABLE--

    // loadJsonFile(filename) reads the jsonfile and returns a pointer to a nlohmann::json-object which
    // is on the heap. loadJsonFile will NOT be responsible for deleting memoy on the heap. thats why
    // we delete the jsonfile object on the heap at the end of this methode
    nlohmann::json* jsonfile = loadJsonFile(filename);

    // get how many frameTags are in the json

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


FrameTag AsepriteManager::getFrameTag(const std::string& filenameTagname)
{
    try
    {
        return frameTags.at(filenameTagname); // for example frameTags["gbFighter-Idle"]
    }
    catch (const std::out_of_range& e)
    {
        std::cerr << "Error: FrameTag " << filenameTagname << " does not exist" << std::endl;
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
