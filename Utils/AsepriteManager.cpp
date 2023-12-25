//
// Created by weitnow on 12/16/23.
//
#include "AsepriteManager.h"

/**
 *
 * @param foldername foldername where the png and json-files are located
 */
AsepriteManager::AsepriteManager(std::string foldername) {
    this->foldername = foldername;
}

AsepriteManager::~AsepriteManager() {
    // delete all pointers and clear memory
    for(auto& pair : animFiles) {
        delete pair.second;
        pair.second = nullptr;
    }
}
/**
 * @brief This function loads a JsonFile and return a pointer to a json-object
 * @param filename filename of a .json-object without .json at the end
 * @return nlohmann::json* : A pointer to a json-object
 */
nlohmann::json* AsepriteManager::loadJsonFile(const std::string& filename) {
    std::string path_with_filename = foldername + filename + ".json";
    std::ifstream i(path_with_filename);
    nlohmann::json* jsondata = new nlohmann::json();
    if (!i) {
        std::cerr << "Failed to open '" << path_with_filename << "'\n";
    } else {
        std::cout << path_with_filename << " successfully loaded\n";
        try {
            // load jsondata from file and put it into nLohmann::json jsondata
            i >> *jsondata;
        } catch (nlohmann::json::parse_error& e) {
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
void AsepriteManager::loadAnimFile(const std::string &filename) {
    AnimationObject* AnimObjPtr = new AnimationObject(filename);
    animFiles[filename] = AnimObjPtr;
    nlohmann::json* jsonfile = loadJsonFile(filename);
    int frameTagSize = (*jsonfile)["meta"]["frameTags"].size();
    std::string name;
    int from;
    int to;
    for (int i = 0; i < frameTagSize; ++i) {
        name = (*jsonfile)["meta"]["frameTags"][i]["name"];
        from = (*jsonfile)["meta"]["frameTags"][i]["from"];
        to = (*jsonfile)["meta"]["frameTags"][i]["to"];
        AnimObjPtr->frameTags[name] = std::pair<int, int>(from, to);
    }
    delete jsonfile;
}

void AsepriteManager::showLoadedAnimFiles() {
    for(auto& pair : animFiles) {
        std::cout << "Filename: " << pair.first << ", Animation object address: " << pair.second << std::endl;
    }
}

auto AsepriteManager::getAnimFile(const std::string& filename )
{

    return animFiles[filename];
}


AnimationObject::AnimationObject(std::string filename) {
    this->filename = filename;




}

