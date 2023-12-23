//
// Created by weitnow on 12/16/23.
//

#ifndef GBFIGHTER_ASEPRITE_H
#define GBFIGHTER_ASEPRITE_H
#include <nlohmann/json.hpp>
#include <string> // Added string include here
#include "raylib.h"
#include <map>

class Aseprite {
private:

    std::string filename;
    Image image;
public:
    Aseprite(std::string filename);
    std::map<std::string, std::pair<int, int>> frameTags;
};

class AsepriteManager {
private:
    std::string foldername;
    nlohmann::json* loadJsonFile();
public:
    AsepriteManager(std::string foldername);
    ~AsepriteManager();
    void loadAnimation(const std::string &filename);

    std::map<std::string, Aseprite*> asepriteObjs;
};



#endif //GBFIGHTER_ASEPRITE_H