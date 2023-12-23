//
// Created by weitnow on 12/16/23.
//
#include "Aseprite.h"

/**
 *
 * @param foldername foldername where the png and json-files are located
 */
AsepriteManager::AsepriteManager(std::string foldername) {
    this->foldername = foldername;
}

AsepriteManager::~AsepriteManager() {
    for(auto& pair : asepriteObjs) {
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

void AsepriteManager::loadAnimation(const std::string &filename) {
    Aseprite* NewAsepritePtr = new Aseprite(filename);
    asepriteObjs[filename] = NewAsepritePtr;
    nlohmann::json* jsonfile = loadJsonFile(filename);
    int frameTagSize = (*jsonfile)["meta"]["frameTags"].size();
    std::string name;
    int from;
    int to;
    for (int i = 0; i < frameTagSize; ++i) {
        name = (*jsonfile)["meta"]["frameTags"][i]["name"];
        from = (*jsonfile)["meta"]["frameTags"][i]["from"];
        to = (*jsonfile)["meta"]["frameTags"][i]["to"];
        NewAsepritePtr->frameTags[name] = std::pair<int, int>(from, to);
    }
    delete jsonfile;
}



void AsepriteManager::showAvailableAnimations() {
    for(auto& pair : asepriteObjs) {
        std::cout << "Filename: " << pair.first << ", Animation object address: " << pair.second << std::endl;
    }

}



Aseprite::Aseprite(std::string filename) {
    this->filename = filename;




}

