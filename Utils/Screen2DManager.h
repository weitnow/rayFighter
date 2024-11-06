#ifndef GBFIGHTER_SCREEN2DMANAGER_H
#define GBFIGHTER_SCREEN2DMANAGER_H

//#include "../Gui/Lifebar.h"
#include "raylib.h"
#include <iostream>
#include <map>


enum class RenderResolution
{
    R_256x144,   // orginal resolution 16:9
    R_512x288,   // x2
    R_768x432,   // x3
    R_1024x576,  // x4
    R_1120x630,  // DEBUG_DRAW
    R_1280x720,  // x5
    R_1536x864,  // x6
    R_1792x1008, // x7
    R_2560x1440  // x10
};

enum class ScreenResolution
{
    S_640x480,   // 4:3
    S_800x600,   // 4:3
    S_1280x720,  // 16:9 HD
    S_1920x1080, // 16:9 Full HD
    S_2560x1440, // 16:9 2K
    S_3440x1440  // 16:9 Ultra Wide
};

class Screen2DManager
{
public:
    Screen2DManager(const ScreenResolution screenResolution,
                    const char* windowTitle,
                    const RenderResolution resolution);

    ~Screen2DManager();

    void beginDrawToRenderTarget();

    void endDrawToRenderTarget();

    void beginDrawToScreen();
    void drawRenderTarget();
    void endDrawToScreen();

    void setRenderResolution(RenderResolution resolution);
    void cycleThroughResolutions();

    Camera2D camera;

private:
    // Member variables
    RenderTexture2D renderTarget; // the renderTarget to draw to, which is 256x144 and will be scaled up
    Rectangle destRec;            // the destination rectangle for the renderTarget (size of the renderTarget)
    Rectangle sourceRec;          // the source rectangle (256x144)
    RenderResolution resolution;  // the resolution the destRec gets set to
    int screenWidth;              // the width of the screen
    int screenHeight;             // the height of the screen
    int resolutionWidth;          // the width of the renderResolution
    int resolutionHeight;         // the height of the renderResolution
    int offsetX;                  // the offset of the rendertarget in relation to screen in x direction
    int offsetY;                  // the offset of the rendertarget in relation to screen in y direction
};

#endif // GBFIGHTER_SCREEN2DMANAGER_H
