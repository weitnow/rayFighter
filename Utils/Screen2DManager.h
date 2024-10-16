#ifndef GBFIGHTER_SCREEN2DMANAGER_H
#define GBFIGHTER_SCREEN2DMANAGER_H

//#include "../Gui/Lifebar.h"
#include "raylib.h"
#include <iostream>
#include <map>


enum class Resolution
{
    R_256x144,
    R_320x180,
    R_480x270,
    R_640x360,
    R_960x540,
    R_1120x630, // DEBUG_DRAW
    R_1920x1080,
    R_2560x1440
};

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
                    const bool windowResizable = false,
                    const Resolution resolution = Resolution::R_1120x630);

    ~Screen2DManager();

    /**
     * @brief Iterates over the membervariable "rendertargets" which is a std::map with RenderTextures and unloads all textures.
     */
    void unloadRenderTarget();

    void update(float deltaTime);

    void beginDrawToRenderTarget();

    /**
     * @brief This has to be called to after finishing drawing to a renderTarget.
     *
     */
    void endDrawToRenderTarget();

    void beginDrawToScreen();
    void drawRenderTarget(std::string renderTargetName);
    void endDrawToScreen();

    void setResolution(Resolution resolution);

    Camera2D camera;

private:
    // Member variables
    RenderTexture2D renderTarget; // the renderTarget to draw to, which is 256x144 and will be scaled up
    Rectangle scaledRectangle;    // used for the DrawTexturePro-Function to draw the renderTarget to Screen
    Resolution resolution;        // the resolution of the destRec
};

#endif // GBFIGHTER_SCREEN2DMANAGER_H
