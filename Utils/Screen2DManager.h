//
// Created by weitnow on 12/26/23.
//

#ifndef GBFIGHTER_SCREEN2DMANAGER_H
#define GBFIGHTER_SCREEN2DMANAGER_H

#include "raylib.h"
#include <iostream>
#include <map>

class Screen2DManager {
public:
    Screen2DManager(const int screenWidth, const int screenHeight, const char* windowTitle);
    ~Screen2DManager();

    void update(float deltaTime);

    void createRenderTarget(std::string renderTargetName, int targetWidth, int targetHeight);
    void beginDrawToRenderTarget(std::string renderTargetName);
    void endDrawToRenderTarget();

    void beginDrawToScreen();
    void drawRenderTarget(std::string renderTargetName);
    void endDrawToScreen();

private:
    // Member variables
    Camera2D camera;
    std::map<std::string, RenderTexture2D> renderTargets;
    Rectangle scaledRectangle; // used for the DrawTexturePro-Function to draw the renderTarget to Screen

    // Functions
    // Function to calculate scaled rectangle dimensions
    Rectangle calculateScaledRectangle(RenderTexture2D renderTarget, int targetWidth, int targetHeight);

};


#endif //GBFIGHTER_SCREEN2DMANAGER_H
