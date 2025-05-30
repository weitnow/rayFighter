#ifndef GBFIGHTER_SCREEN2DMANAGER_H
#define GBFIGHTER_SCREEN2DMANAGER_H

//#include "../Gui/Lifebar.h"
#include "raylib.h"
#include <iostream>
#include <map>

class AsepriteAnimationFile; // Forward declaration
class AsepriteManager;       // Forward declaration


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
    S_640x480,   // 4:3                 // enum 0
    S_800x600,   // 4:3                 // enum 1
    S_1280x720,  // 16:9 HD             // enum 2
    S_1920x1080, // 16:9 Full HD        // enum 3
    S_2560x1440, // 16:9 2K             // enum 4
    S_3440x1440  // 16:9 Ultra Wide     // enum 5
};

inline int EnumToValue(RenderResolution resolution)
{
    switch (resolution)
    {
    case RenderResolution::R_256x144:
        std::cout << "1 R_256x144->";
        return 1;
    case RenderResolution::R_512x288:
        std::cout << "2 R_512x288->";
        return 2;
    case RenderResolution::R_768x432:
        std::cout << "3 R_768x432->";
        return 3;
    case RenderResolution::R_1024x576:
        std::cout << "4 R_1024x576->";
        return 4;
    case RenderResolution::R_1120x630: // DEBUG_DRAW
        std::cout << "5 R_1120x630->";
        return 5;
    case RenderResolution::R_1280x720:
        std::cout << "6 R_1280x720->";
        return 6;
    case RenderResolution::R_1536x864:
        std::cout << "7 R_1536x864->";
        return 7;
    case RenderResolution::R_1792x1008:
        std::cout << "8 R_1792x1008->";
        return 8;
    case RenderResolution::R_2560x1440:
        std::cout << "9 R_2560x1440->";
        return 9;
    default:
        return 1;
    }
}

struct ScreenShake
{
    bool isShaking = false;
    float intensity = 0.0f;               // Maximum offset in pixels
    float duration = 0.0f;                // Total shake duration in seconds
    float elapsedTime = 0.0f;             // Time passed since shake started
    Vector2 currentOffset = {0.0f, 0.0f}; // Current shake offset
};


class Screen2DManager
{
public:
    Screen2DManager(const char* windowTitle);

    ~Screen2DManager();

    void takeReferenceToAsepriteManager(AsepriteManager* asepriteManager);

    void beginDrawToRenderTarget();

    void endDrawToRenderTarget();

    void beginDrawToScreen();
    void drawRenderTarget();
    void endDrawToScreen();

    void update(float deltaTime);
    void draw();        // ScreenEffects
    void drawOverlay(); // draw the gameboy Overlay

    int getScreenResolution();                                // returns and int (not a enum)
    void changeScreenResolution(ScreenResolution resolution); // will also adjust RenderResolution to the best fit
    void cycleThroughRenderResolutions();
    void saveScreenResolution();
    bool loadScreenResolution();

    // ===== Effects ======
    // Screen Shake
    void startScreenShake(float intensity, float duration);
    // Fade Effect
    bool isFadeEffectPlaying() const
    {
        return _fadeEffectPlaying;
    }
    void fadeEffect(float speed, float targetAlpha);
    float getFadeAlpha() const
    {
        return _currentAlpha;
    }
    // Slide Effect
    bool isSlideEffectPlaying() const
    {
        return _slideEffectPlaying;
    }
    void slideEffect(float speed, int slideOffset);
    int getSlideOffset() const
    {
        return _current_slideOffset;
    }


    void loadScreenGenericEffects(const std::string& nameAnimFile);
    void setScreenGenericEffects(const std::string& frameTag,
                                 int playHowOften = 1); // if playHowOften is -1, the animation will be looped

    Camera2D camera;

    // declare DebugInfo as friendclass, because it calls _setRenderResolution
    friend class DebugInfo;

private:
    // Member variables
    Texture2D gameboyOverlay;       // the overlay texture
    float _scaleFactorOverlay = 0;  // calculated in _calculateOverlaySize
    float _scaledOverlayHeight = 0; // calculated in _calculateOverlaySize
    float _scaledOverlayWidth = 0;  // calculated in _calculateOverlaySize
    float _overlayOffsetX = 0;      // calculated in _calculateOverlaySize
    float _overlayOffsetY = 0;      // calculated in _calculateOverlaySize

    RenderTexture2D renderTarget;      // the renderTarget to draw to, which is 256x144 and will be scaled up
    Rectangle destRec;                 // the destination rectangle for the renderTarget (size of the renderTarget)
    Rectangle sourceRec;               // the source rectangle (256x144)
    RenderResolution renderResolution; // the resolution the destRec gets set to
    ScreenResolution screenResolution; // the screenresolution (screenWidth/screenHeight)
    int screenWidth;                   // the width of the screen
    int screenHeight;                  // the height of the screen
    int resolutionWidth;               // the width of the renderResolution
    int resolutionHeight;              // the height of the renderResolution
    int offsetX;                       // the offset of the rendertarget in relation to screen in x direction
    int offsetY;                       // the offset of the rendertarget in relation to screen in y direction

    ScreenShake shake; // the screen shake object

    AsepriteManager* asepriteManager; // first execute takeReferenceToAsepriteManager otherwise this will be nullptr

    AsepriteAnimationFile* screenGenericEffectsAnimFile;
    int screenGenericPlayHowOften = 0; //how often the effect should be played, -1 = loop
    bool screenGenericEffectPlaying = false;
    int counterGenericEffectPlaying = 0;    // counts how many times the effect has been played in a row
    bool _animJustFinished = false;         // bool of the animation file
    bool _previousAnimJustFinished = false; // bool of the animation file

    // Fade Effect
    void _updateFadeEffect(float deltaTime);
    bool _fadeEffectPlaying = false;
    float _fadeSpeed = 0.0f;
    float _currentAlpha = 0.0f;
    float _targetAlpha = 0.0f;

    // Slide Effect
    void _updateSlideEffect(float deltaTime);
    bool _slideEffectPlaying = false;
    float _slideSpeed = 0.0f;
    int _current_slideOffset = 0;
    int _target_slideOffset = 0;

    // Member functions
    void _calculateOverlaySize();
    void _setRenderResolution(RenderResolution resolution);
    void _setScreenResolution(ScreenResolution resolution);
    void _updateScreenShake(float deltaTime);          // private, is called in update
    void _updateScreenGenericEffects(float deltaTime); // private, is called in update
    void _unloadScreenGenericEffects();                // will be called in the destructor
};

#endif // GBFIGHTER_SCREEN2DMANAGER_H
