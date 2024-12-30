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
    _setScreenResolution(screenResolution);

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

    // load the gameboy overlay
    gameboyOverlay = LoadTexture("Assets/Graphics/overlay.png");

    // calculate the gameboy overlay size
    _calculateOverlaySize();

    // set Resolution of the destRec (not the screen resolution)
    this->_setRenderResolution(resolution);
}

Screen2DManager::~Screen2DManager()
{
    UnloadRenderTexture(renderTarget); // Raylib function

    UnloadTexture(gameboyOverlay); // Raylib function

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
    _updateFadeEffect(deltaTime);
    _updateSlideEffect(deltaTime);
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
    // Draw fade effect rectangle
    DrawRectangle(0, 0, Constants::RENDERTARGET_WIDTH, Constants::RENDERTARGET_HEIGHT, Fade(BLACK, _currentAlpha));


    // Draw slide effect rectangle top
    DrawRectangle(0, 0, Constants::RENDERTARGET_WIDTH, _current_slideOffset, BLACK);
    // Draw slide effect rectangle bottom
    DrawRectangle(0,
                  Constants::RENDERTARGET_HEIGHT - _current_slideOffset,
                  Constants::RENDERTARGET_WIDTH,
                  _current_slideOffset,
                  BLACK);
}

void Screen2DManager::drawOverlay()
{
    DrawTextureEx(gameboyOverlay, (Vector2){_overlayOffsetX, _overlayOffsetY}, 0.0f, _scaleFactorOverlay, WHITE);
}

void Screen2DManager::_setRenderResolution(RenderResolution resolution)
{
    this->resolution = resolution;

    if (resolution == RenderResolution::R_256x144)
    {
        resolutionWidth = 256;
        resolutionHeight = 144;
    }
    else if (resolution == RenderResolution::R_512x288) // used for 640x480 with GB Overlay
    {
        resolutionWidth = 512;
        resolutionHeight = 288;
    }
    else if (resolution == RenderResolution::R_768x432) // used for 1280x720 and 800 x 600 with GB overlay
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
    else if (resolution == RenderResolution::R_1280x720) // used for 1920 x 1080 with GB overlay
    {
        resolutionWidth = 1280;
        resolutionHeight = 720;
    }
    else if (resolution == RenderResolution::R_1536x864)
    {
        resolutionWidth = 1536;
        resolutionHeight = 864;
    }
    else if (resolution == RenderResolution::R_1792x1008) // used for 2560 x 1440 and 3440 x 1440 with GB overlay
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

void Screen2DManager::changeScreenResolution(ScreenResolution resolution)
{
    // set Screen Resolution
    _setScreenResolution(resolution);


    // set Resolution of the renderTarget
    switch (resolution)
    {
    case ScreenResolution::S_640x480:
        _setRenderResolution(RenderResolution::R_512x288);
        break;
    case ScreenResolution::S_800x600:
        _setRenderResolution(RenderResolution::R_768x432);
        break;
    case ScreenResolution::S_1280x720:
        _setRenderResolution(RenderResolution::R_768x432);
        break;
    case ScreenResolution::S_1920x1080:
        _setRenderResolution(RenderResolution::R_1280x720);
        break;
    case ScreenResolution::S_2560x1440:
        _setRenderResolution(RenderResolution::R_1792x1008);
        break;
    case ScreenResolution::S_3440x1440:
        _setRenderResolution(RenderResolution::R_1792x1008);
        break;
    }

    // change screen height and width
    SetWindowSize(screenWidth, screenHeight); // Raylib function

    // calculate the gameboy overlay size
    _calculateOverlaySize();
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
    _setRenderResolution(newResolution);
}

std::string Screen2DManager::_screenResolutionToString(ScreenResolution resolution)
{
    switch (resolution)
    {
    case ScreenResolution::S_640x480:
        return "640x480";
    case ScreenResolution::S_800x600:
        return "800x600";
    case ScreenResolution::S_1280x720:
        return "1280x720";
    case ScreenResolution::S_1920x1080:
        return "1920x1080";
    case ScreenResolution::S_2560x1440:
        return "2560x1440";
    case ScreenResolution::S_3440x1440:
        return "3440x1440";
    default:
        return "Unknown";
    }
}

std::array<ScreenResolution, 6> Screen2DManager::GetAllScreenResolutionEnums()
{
    return {ScreenResolution::S_640x480,
            ScreenResolution::S_800x600,
            ScreenResolution::S_1280x720,
            ScreenResolution::S_1920x1080,
            ScreenResolution::S_2560x1440,
            ScreenResolution::S_3440x1440};
}

void Screen2DManager::startScreenShake(float intensity, float duration)
{
    shake.isShaking = true;
    shake.intensity = intensity;
    shake.duration = duration;
    shake.elapsedTime = 0.0f;
    shake.currentOffset = {0.0f, 0.0f};
}

void Screen2DManager::fadeEffect(float speed, float targetAlpha)
{
    _fadeEffectPlaying = true;
    _fadeSpeed = speed;
    _targetAlpha = targetAlpha;
}

void Screen2DManager::_updateSlideEffect(float deltaTime)
{
    if (!_slideEffectPlaying)
    {
        return;
    }

    // check if target and current slide offset are the same
    if (_current_slideOffset == _target_slideOffset)
    {
        _slideEffectPlaying = false;
        return;
    }

    // otherwise move the slide
    if (_current_slideOffset < _target_slideOffset)
    {
        _current_slideOffset += _slideSpeed * deltaTime;
        if (_current_slideOffset > _target_slideOffset)
        {
            _current_slideOffset = _target_slideOffset;
        }
    }
    else
    {
        _current_slideOffset -= _slideSpeed * deltaTime;
        if (_current_slideOffset < _target_slideOffset)
        {
            _current_slideOffset = _target_slideOffset;
        }
    }
}

void Screen2DManager::_calculateOverlaySize()
{
    // calculate scaleFactor of the gameboyOverlayTexture to fit the height of the screen
    _scaleFactorOverlay = (float)screenHeight / gameboyOverlay.height;

    // calculate the scaled height and width of the overlay
    _scaledOverlayWidth = gameboyOverlay.width * _scaleFactorOverlay;
    _scaledOverlayHeight = gameboyOverlay.height * _scaleFactorOverlay;

    // Calculate the X position to center the texture
    _overlayOffsetX = (screenWidth - _scaledOverlayWidth) / 2.0f;
    _overlayOffsetY = 0.0f; // Always start at the top of the screen
}

void Screen2DManager::_setScreenResolution(ScreenResolution resolution)
{
    if (resolution == ScreenResolution::S_640x480)
    {
        screenWidth = 640;
        screenHeight = 480;
    }
    else if (resolution == ScreenResolution::S_800x600)
    {
        screenWidth = 800;
        screenHeight = 600;
    }
    else if (resolution == ScreenResolution::S_1280x720)
    {
        screenWidth = 1280;
        screenHeight = 720;
    }
    else if (resolution == ScreenResolution::S_1920x1080)
    {
        screenWidth = 1920;
        screenHeight = 1080;
    }
    else if (resolution == ScreenResolution::S_2560x1440)
    {
        screenWidth = 2560;
        screenHeight = 1440;
    }
    else if (resolution == ScreenResolution::S_3440x1440)
    {
        screenWidth = 3440;
        screenHeight = 1440;
    }
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
        _animJustFinished = screenGenericEffectsAnimFile->hasAnimJustFinished();
        std::cout << "_animJustFinished=" << _animJustFinished << std::endl;

        if (_animJustFinished != _previousAnimJustFinished)
        {
            // increase counter only if _animJustFinished returned true
            if (_animJustFinished)
            {
                counterGenericEffectPlaying++;
            }

            _previousAnimJustFinished = _animJustFinished;
        }

        if (screenGenericPlayHowOften != -1 && counterGenericEffectPlaying >= screenGenericPlayHowOften &&
            _animJustFinished)
        {
            screenGenericEffectPlaying = false;
            screenGenericEffectsAnimFile->resetBools();
            screenGenericEffectsAnimFile
                ->setCurrentFrameToMinFrame(); // otherwise the next animation might not start with the startframe
            counterGenericEffectPlaying = 0;
            _animJustFinished = false;
            _previousAnimJustFinished = false;
        }

        screenGenericEffectsAnimFile->update(deltaTime);
    }
}


void Screen2DManager::slideEffect(float speed, int slideOffset)
{
    _slideEffectPlaying = true;
    _slideSpeed = speed * 20;
    _target_slideOffset = Utils::clamp(slideOffset, 0, 72); // 72 is full black screen
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
    screenGenericEffectsAnimFile->setFrameTag(frameTag);
    screenGenericPlayHowOften = playHowOften;
    counterGenericEffectPlaying = 0;
    screenGenericEffectPlaying = true;
}

void Screen2DManager::_updateFadeEffect(float deltaTime)
{
    if (!_fadeEffectPlaying)
    {
        return;
    }

    if (_currentAlpha == _targetAlpha)
    {
        _fadeEffectPlaying = false;
        return;
    }

    // Otherwise, update the alpha value
    _currentAlpha += (_targetAlpha > _currentAlpha ? 1 : -1) * _fadeSpeed * deltaTime;

    // Clamp the alpha value between 0 and 1
    _currentAlpha = Utils::clamp(_currentAlpha, 0.0f, 1.0f); // Ensure alpha is between 0 and 1
}

void Screen2DManager::_unloadScreenGenericEffects()
{
    if (screenGenericEffectsAnimFile != nullptr)
    {
        delete screenGenericEffectsAnimFile;
        screenGenericEffectsAnimFile = nullptr;
    }
}
