//
// Created by weitnow on 12/16/23.
//

#ifndef GBFIGHTER_ASEPRITEMANAGER_H
#define GBFIGHTER_ASEPRITEMANAGER_H

#include <nlohmann/json.hpp>
#include <string> // Added string include here
#include "raylib.h"
#include <map>
#include <fstream>
#include <iostream>

class AnimationObject {
private:
    std::string filename;
    Image image;
public:
    // constructor
    explicit AnimationObject(std::string filename);

    // member variable
    std::map<std::string, std::pair<int, int>> frameTags;
};

class AsepriteManager {
public:
    explicit AsepriteManager(std::string foldername);
    ~AsepriteManager();

    // methods
    void loadAnimFile(const std::string &filename);
    void showLoadedAnimFiles();
    auto getAnimFile(const std::string& filename);

    // member variable
    std::map<std::string, AnimationObject*> animFiles; // map<animationfilename><animationobject*>
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



#endif //GBFIGHTER_ASEPRITEMANAGER_H