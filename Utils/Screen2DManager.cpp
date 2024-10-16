#include "Screen2DManager.h"
#include "../Constants.h"

Screen2DManager::Screen2DManager(const int screenWidth,
                                 const int screenHeight,
                                 const char* windowTitle,
                                 const bool windowResizable,
                                 const Resolution resolution)

{
    if (windowResizable)
    {
        // Set the window to be resizable, this needs to be done befor calling InitWindow(), otherwise it has no affect
        SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    }

    // Initialize window
    InitWindow(screenWidth, screenHeight, windowTitle);

    // Initialize Camera
    camera.target = Vector2{0.0f, 0.0f};
    camera.offset = Vector2{0.0f, 0.0f};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    // initialize the rernderTarget with 256x144
    renderTarget = LoadRenderTexture(Constants::RENDERTARGET_WIDTH, Constants::RENDERTARGET_HEIGHT);
    sourceRec = {0.0f, 0.0f, Constants::RENDERTARGET_WIDTH, -Constants::RENDERTARGET_HEIGHT};

    // set Resolution of the destRec (not the screen resolution)
    this->setResolution(resolution);
}

Screen2DManager::~Screen2DManager()
{
}

void Screen2DManager::init()
{
    // Set  game to run at X frames-per-second (recommended: 60)
    SetTargetFPS(Constants::FPS); // Raylib function

    // Set the resolution/size of the of the renderTarget (not the screen resolution), default is 1120x630
    // setResolution(Resolution::R_1920x1080);
    // setResolution(Resolution::R_2560x1440);
}

void Screen2DManager::unloadRenderTarget()
{
    std::cout << "Unloading texture with id: " << renderTarget.texture.id << std::endl;
    UnloadRenderTexture(renderTarget); // Raylib function
}

void Screen2DManager::update(float deltaTime)
{
    /*
    // Camera rotation controls
    if (IsKeyDown(KEY_W))
        camera.rotation--;
    else if (IsKeyDown(KEY_S))
        camera.rotation++;

    // Camera zoom controls
    if (IsKeyDown(KEY_I))
        camera.zoom += 0.01f;
    if (IsKeyDown(KEY_U))
        camera.zoom -= 0.01f;
    */
    // Camera x controls
    if (IsKeyDown(KEY_N))
        camera.target.x--;
    if (IsKeyDown(KEY_M))
        camera.target.x++;
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

void Screen2DManager::setResolution(Resolution resolution)
{
    this->resolution = resolution;

    if (resolution == Resolution::R_256x144)
    {
        destRec = {0.0f, 0.0f, 256, 144};
    }
    else if (resolution == Resolution::R_320x180)
    {
        destRec = {0.0f, 0.0f, 320, 180};
    }
    else if (resolution == Resolution::R_480x270)
    {
        destRec = {0.0f, 0.0f, 480, 270};
    }
    else if (resolution == Resolution::R_640x360)
    {
        destRec = {0.0f, 0.0f, 640, 360};
    }
    else if (resolution == Resolution::R_960x540)
    {
        destRec = {0.0f, 0.0f, 960, 540};
    }
    else if (resolution == Resolution::R_1120x630)
    {
        destRec = {10.0f, 420.0f, 1120, 630};
    }
    else if (resolution == Resolution::R_1920x1080)
    {
        destRec = {0.0f, 0.0f, 1920, 1080};
    }
    else if (resolution == Resolution::R_2560x1440)
    {
        destRec = {0.0f, 0.0f, 2560, 1440};
    }
}
