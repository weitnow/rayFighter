//
// Created by weitnow on 12/16/23.
//

#ifndef GBFIGHTER_ASEPRITE_H
#define GBFIGHTER_ASEPRITE_H

#include <nlohmann/json.hpp>
#include <string> // Added string include here
#include "raylib.h"
#include <map>
#include <fstream>
#include <iostream>

class Aseprite {
private:
    std::string filename;
    Image image;
public:
    explicit Aseprite(std::string filename);
    std::map<std::string, std::pair<int, int>> frameTags;
};

class AsepriteManager {
public:
    explicit AsepriteManager(std::string foldername);
    ~AsepriteManager();

    // methods
    void loadAnimation(const std::string &filename);
    void showAvailableAnimations();

    // fields
    std::map<std::string, Aseprite*> asepriteObjs;
private:
    std::string foldername;
    nlohmann::json* loadJsonFile(const std::string& filename);
};

struct FrameTag{
    std::string name;
    int from;
    int to;
    void print() const {
        std::cout << "Tag: " << name << "\n from: " << from << "\n to: " << to << std::endl;
    }
};



#endif //GBFIGHTER_ASEPRITE_H