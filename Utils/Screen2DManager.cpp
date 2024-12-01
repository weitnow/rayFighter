#include "Screen2DManager.h"
#include "../Constants.h"
#include "AsepriteManager.h"
#include "HelperFunctions.h"


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
      offsetX(0), offsetY(0), screenGenericEffectsAnimFile{nullptr}, asepriteManager{nullptr}
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

    if (screenGenericEffectsAnimFile != nullptr)
    {
        delete screenGenericEffectsAnimFile;
    }
}

void Screen2DManager::takeReferenceToAsepriteManager(AsepriteManager* asepriteManager)
{
    this->asepriteManager = asepriteManager;
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

void Screen2DManager::update(float deltaTime)
{
    _updateScreenShake(deltaTime);
    _updateScreenGenericEffects(deltaTime);
}

void Screen2DManager::draw()
{
    if (screenGenericEffectPlaying)
    {
        screenGenericEffectsAnimFile->drawCurrentSelectedTag(0,
                                                             40,
                                                             1,
                                                             WHITE); // y value = 40 because the hud is 40px high
    }
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

    if (Global::debugMode)
    {
        offsetX = 10;
        offsetY = 410;
    }
    else
    {
        offsetX = (screenWidth - resolutionWidth) / 2;
        offsetY = (screenHeight - resolutionHeight) / 2;
    }


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

void Screen2DManager::startScreenShake(float intensity, float duration)
{
    shake.isShaking = true;
    shake.intensity = intensity;
    shake.duration = duration;
    shake.elapsedTime = 0.0f;
    shake.currentOffset = {0.0f, 0.0f};
}

void Screen2DManager::_updateScreenShake(float deltaTime)
{

    if (shake.isShaking)
    {
        shake.elapsedTime += deltaTime;

        if (shake.elapsedTime < shake.duration)
        {
            // Generate random offsets with float precision
            shake.currentOffset.x = ((rand() / (float)RAND_MAX) * 2.0f - 1.0f) * shake.intensity;
            shake.currentOffset.y = ((rand() / (float)RAND_MAX) * 2.0f - 1.0f) * shake.intensity;
        }
        else
        {
            // End shake
            shake.isShaking = false;
            shake.currentOffset = {0.0f, 0.0f};
        }
    }

    // Apply the shake offset to the camera
    camera.offset.x = shake.currentOffset.x;
    camera.offset.y = shake.currentOffset.y;
}

void Screen2DManager::_updateScreenGenericEffects(float deltaTime)
{
    if (screenGenericEffectPlaying)
    {
        screenGenericEffectsAnimFile->update(deltaTime);

        if (screenGenericEffectsAnimFile->hasAnimJustFinished())
        {

            if (_animJustFinished != _previousAnimJustFinished)
            {
                counterGenericEffectPlaying++;
                _previousAnimJustFinished = _animJustFinished;
            }

            if (screenGenericPlayHowOften != -1 && counterGenericEffectPlaying >= screenGenericPlayHowOften)
            {
                screenGenericEffectPlaying = false;
                screenGenericEffectsAnimFile->resetBools();
                counterGenericEffectPlaying = 0;
            }
        }
        std::cout << "counterGenericEffectPlaying: " << counterGenericEffectPlaying << std::endl;
    }
}

void Screen2DManager::loadScreenGenericEffects(const std::string& nameAnimFile)
{
    if (screenGenericEffectsAnimFile != nullptr)
    {
        // unload the current screenGenericEffectsAnimFile
        delete screenGenericEffectsAnimFile;
        screenGenericEffectsAnimFile = nullptr;
        // raise a warning
        std::cout << "Screen2DManager::loadScreenGenericEffects -> screenGenericEffectsAnimFile was already loaded, "
                     "unloaded existing file and reloaded specified file"
                  << std::endl;
    }

    // load file
    screenGenericEffectsAnimFile = asepriteManager->getAnimFile(nameAnimFile);
}

void Screen2DManager::setScreenGenericEffects(const std::string& frameTag, int playHowOften)
{
    if (screenGenericEffectsAnimFile == nullptr)
    {
        throw std::runtime_error("Screen2DManager::setScreenGenericEffects -> screenGenericEffectsAnimFile is nullptr");
    }
    screenGenericEffectsAnimFile->resetBools();
    screenGenericPlayHowOften = playHowOften;
    counterGenericEffectPlaying = 0;
    screenGenericEffectPlaying = true;
    screenGenericEffectsAnimFile->setFrameTag(frameTag);
}

void Screen2DManager::_unloadScreenGenericEffects()
{
    if (screenGenericEffectsAnimFile != nullptr)
    {
        delete screenGenericEffectsAnimFile;
        screenGenericEffectsAnimFile = nullptr;
    }
}
