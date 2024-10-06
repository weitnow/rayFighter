//
// Created by weitnow on 12/26/23.
//

#ifndef GBFIGHTER_SCREEN2DMANAGER_H
#define GBFIGHTER_SCREEN2DMANAGER_H

#include "../Gui/Lifebar.h"
#include "raylib.h"
#include <iostream>
#include <map>

/**
 * @class Screen2Dmanager
 * @brief Manages 2D screen. It created the gaming window and is rendering assets to the screen using render targets
 * @param[in] screenWidth the width of the game window on the screen
 * @param[in] screenHeight the height of the game window on the screen
 * @param[in] windowTitle the title of the game window
 * @param[in] windowResize optional, if set to true, the window will be resizable
 */
class Screen2DManager
{
public:
    Screen2DManager(const int screenWidth,
                    const int screenHeight,
                    const char* windowTitle,
                    const bool windowResizable = false);

    ~Screen2DManager();

    /**
     * @brief Iterates over the membervariable "rendertargets" which is a std::map with RenderTextures and unloads all textures.
     */
    void unloadAllRenderTextures();

    void update(float deltaTime);

    /**
     * @brief Create a Render Target object and store it in the member variable renderTargets of this class.
     * The rendertarget will be scaled up to the width and height of the gaming window
     *
     * @param renderTargetName the name of the rendertarget.
     * @param targetWidth the width of the rendertarget
     * @param targetHeight the height of the rendertarget
     *
     */
    void createRenderTarget(std::string renderTargetName, int targetWidth, int targetHeight);

    /**
     * @brief This methode will start the draw process to the rendertarget. make sure that you end it with endDrawToRenderTarget-Methode of the Screen2DManager.
     * For example: screen2Dmanager.beginDrawToRenderTarget("mainRenderTarget"); #DRAW SOMEHTING; screen2DManager.endDrawToRenderTarget();
     *
     * @param renderTargetName Name of the rendertarget, which has before to be created with the createRenderTarget-Methode of Screen2DManager
     */
    void beginDrawToRenderTarget(std::string renderTargetName);

    /**
     * @brief This has to be called to after finishing drawing to a renderTarget.
     *
     */
    void endDrawToRenderTarget();

    void beginDrawToScreen();
    void drawRenderTarget(std::string renderTargetName);
    void endDrawToScreen();

private:
    // Member variables
    Camera2D camera;
    std::map<std::string, RenderTexture2D> renderTargets;
    Rectangle scaledRectangle; // used for the DrawTexturePro-Function to draw the renderTarget to Screen

    // Lifebar
    Lifebar lifebar1;
    Lifebar lifebar2;

    // Functions
    // Function to calculate scaled rectangle dimensions
    Rectangle calculateScaledRectangle(RenderTexture2D renderTarget, int targetWidth, int targetHeight);
};

#endif // GBFIGHTER_SCREEN2DMANAGER_H
