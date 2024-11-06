#include "Screen2DManager.h"
#include "../Constants.h"


int EnumToValue(RenderResolution resolution)
{
    switch (resolution)
    {
    case RenderResolution::R_256x144:
        return 1;
    case RenderResolution::R_512x288:
        return 2;
    case RenderResolution::R_768x432:
        return 3;
    case RenderResolution::R_1024x576:
        return 4;
    case RenderResolution::R_1120x630:
        return 5;
    case RenderResolution::R_1280x720:
        return 5;
    case RenderResolution::R_1536x864:
        return 6;
    case RenderResolution::R_1792x1008:
        return 7;
    case RenderResolution::R_2560x1440:
        return 10;
    default:
        return 1;
    }
}

Screen2DManager::Screen2DManager(const ScreenResolution screenResolution,
                                 const char* windowTitle,
                                 const RenderResolution resolution)
    : resolution(resolution), screenWidth(0), screenHeight(0), camera{0}, destRec{0}, sourceRec{0}, renderTarget{0},
      offsetX(0), offsetY(0)
{

    // Set the screen width and height
    if (screenResolution == ScreenResolution::S_640x480)
    {
        screenWidth = 640;
        screenHeight = 480;
    }
    else if (screenResolution == ScreenResolution::S_800x600)
    {
        screenWidth = 800;
        screenHeight = 600;
    }
    else if (screenResolution == ScreenResolution::S_1280x720)
    {
        screenWidth = 1280;
        screenHeight = 720;
    }
    else if (screenResolution == ScreenResolution::S_1920x1080)
    {
        screenWidth = 1920;
        screenHeight = 1080;
    }
    else if (screenResolution == ScreenResolution::S_2560x1440)
    {
        screenWidth = 2560;
        screenHeight = 1440;
    }
    else if (screenResolution == ScreenResolution::S_3440x1440)
    {
        screenWidth = 3440;
        screenHeight = 1440;
    }

    // Initialize window
    InitWindow(screenWidth, screenHeight, windowTitle);

    // Set  game to run at X frames-per-second (recommended: 60)
    SetTargetFPS(Constants::FPS); // Raylib function

    // Initialize Camera
    camera.target = Vector2{0.0f, 0.0f};
    camera.offset = Vector2{0.0f, 0.0f};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    // initialize the rernderTarget with 256x144
    renderTarget = LoadRenderTexture(Constants::RENDERTARGET_WIDTH, Constants::RENDERTARGET_HEIGHT);
    sourceRec = {0.0f, 0.0f, Constants::RENDERTARGET_WIDTH, -Constants::RENDERTARGET_HEIGHT};

    // set Resolution of the destRec (not the screen resolution)
    this->setRenderResolution(resolution);
}

Screen2DManager::~Screen2DManager()
{
    UnloadRenderTexture(renderTarget); // Raylib function
}

void Screen2DManager::beginDrawToScreen()
{
    BeginDrawing(); // Raylib function
}

void Screen2DManager::beginDrawToRenderTarget()
{
    BeginTextureMode(renderTarget); // Raylib function
}

void Screen2DManager::drawRenderTarget()
{
    DrawTexturePro(renderTarget.texture, sourceRec, destRec, Vector2{0, 0}, 0.0f, WHITE);
}

void Screen2DManager::endDrawToRenderTarget()
{
    EndTextureMode(); // Raylib function
}

void Screen2DManager::endDrawToScreen()
{
    EndDrawing(); // Raylib function
}

void Screen2DManager::setRenderResolution(RenderResolution resolution)
{
    this->resolution = resolution;

    if (resolution == RenderResolution::R_256x144)
    {
        resolutionWidth = 256;
        resolutionHeight = 144;
    }
    else if (resolution == RenderResolution::R_512x288)
    {
        resolutionWidth = 512;
        resolutionHeight = 288;
    }
    else if (resolution == RenderResolution::R_768x432)
    {
        resolutionWidth = 768;
        resolutionHeight = 432;
    }
    else if (resolution == RenderResolution::R_1024x576)
    {
        resolutionWidth = 1024;
        resolutionHeight = 576;
    }
    else if (resolution == RenderResolution::R_1120x630) // DEBUG_DRAW
    {
        resolutionWidth = 1120;
        resolutionHeight = 630;
    }
    else if (resolution == RenderResolution::R_1280x720)
    {
        resolutionWidth = 1280;
        resolutionHeight = 720;
    }
    else if (resolution == RenderResolution::R_1536x864)
    {
        resolutionWidth = 1536;
        resolutionHeight = 864;
    }
    else if (resolution == RenderResolution::R_1792x1008)
    {
        resolutionWidth = 1792;
        resolutionHeight = 1008;
    }
    else if (resolution == RenderResolution::R_2560x1440)
    {
        resolutionWidth = 2560;
        resolutionHeight = 1440;
    }

    offsetX = (screenWidth - resolutionWidth) / 2;
    offsetY = (screenHeight - resolutionHeight) / 2;

    destRec = {static_cast<float>(offsetX),
               static_cast<float>(offsetY),
               static_cast<float>(resolutionWidth),
               static_cast<float>(resolutionHeight)};
}

void Screen2DManager::cycleThroughResolutions()
{
    int value = EnumToValue(resolution);
    value++;
    if (value > 10)
    {
        value = 1;
    }
    RenderResolution newResolution = static_cast<RenderResolution>(value);
    setRenderResolution(newResolution);
}
