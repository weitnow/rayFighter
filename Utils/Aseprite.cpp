//
// Created by weitnow on 12/16/23.
//

#include "Aseprite.h"

#include <fstream>
#include <iostream>

struct FrameTag{
    std::string name;
    int from;
    int to;
};



nlohmann::json* AsepriteManager::loadJsonFile() {
    std::ifstream i("Assets/Graphics/gbFighter.json");
    nlohmann::json* jsondata = new nlohmann::json();
    if (!i) {
        std::cerr << "Failed to open 'Assets/Graphics/gbFighter.json'\n";
    } else {
        try {

            i >> *jsondata;
        } catch (nlohmann::json::parse_error& e) {
            std::cerr << "Failed to parse JSON: " << e.what() << "\n";
            delete jsondata;
        }
    }
    i.close();

    if(jsondata){
        return jsondata;
    }
    return nullptr;

}


AsepriteManager::AsepriteManager(std::string foldername) {
    this->foldername = foldername;
}

AsepriteManager::~AsepriteManager() {
    for(auto& pair : asepriteObjs) {
        delete pair.second;
        pair.second = nullptr;
    }
}

void AsepriteManager::loadAnimation(const std::string &filename) {
    Aseprite* NewAsepritePtr = new Aseprite(filename);
    asepriteObjs[filename] = NewAsepritePtr;
    nlohmann::json* jsonfile = loadJsonFile();
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


Aseprite::Aseprite(std::string filename) {
    this->filename = filename;




}

