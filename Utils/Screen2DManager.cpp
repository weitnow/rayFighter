//
// Created by weitnow on 12/26/23.
//

#include "Screen2DManager.h"

Screen2DManager::Screen2DManager(const int screenWidth,
                                 const int screenHeight,
                                 const char* windowTitle,
                                 const bool windowResizable)

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
}

Screen2DManager::~Screen2DManager()
{
}

void Screen2DManager::unloadAllRenderTextures()
{
    // Iterate over the map of renderTargets and unload all textures
    for (auto& pair : renderTargets)
    {
        if (pair.second.texture.id != 0)
        {
            // print texture.id to console
            std::cout << "Unloading texture with id: " << pair.second.texture.id << std::endl;
            UnloadRenderTexture(pair.second); // pair.first is the key, pair.second is the value
        }
    }
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
    if (IsKeyDown(KEY_B))
        camera.target.x--;
    if (IsKeyDown(KEY_N))
        camera.target.x++;
}

void Screen2DManager::createRenderTarget(std::string renderTargetName, int targetWidth, int targetHeight)
{
    RenderTexture2D renderTexture = LoadRenderTexture(targetWidth, targetHeight);
    renderTargets[renderTargetName] = renderTexture;
}

void Screen2DManager::beginDrawToScreen()
{
    BeginDrawing(); // Raylib function
}

void Screen2DManager::beginDrawToRenderTarget(std::string renderTargetName)
{
    BeginTextureMode(renderTargets[renderTargetName]);
}

void Screen2DManager::drawRenderTarget(std::string renderTargetName)
{
    RenderTexture2D renderTarget = renderTargets[renderTargetName];
    //scaledRectangle = calculateScaledRectangle(renderTarget, renderTarget.texture.width, renderTarget.texture.height);
    scaledRectangle =
        alternativeCalculateScaledRectangle(renderTarget, renderTarget.texture.width, renderTarget.texture.height);

    /*
    DrawTexturePro(renderTarget.texture,
                   (Rectangle){0.0f, 0.0f, (float)renderTarget.texture.width, (float)-renderTarget.texture.height},
                   scaledRectangle,
                   (Vector2){0, 0},
                   0.0f,
                   WHITE);
    */
    Rectangle sourceRec = {0.0f, 0.0f, 240, -135};
    Rectangle destRec = {0.0f, 540.0f * 0.8, 960 * 1.2, 540 * 1.2};

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

Rectangle Screen2DManager::calculateScaledRectangle(RenderTexture2D renderTarget, int targetWidth, int targetHeight)
{
    renderTarget.texture.height = GetScreenHeight();
    renderTarget.texture.width = (float)renderTarget.texture.height * ((float)targetWidth / (float)targetHeight);
    int scaleHangover = 0;

    if (renderTarget.texture.width > GetScreenWidth())
    {
        renderTarget.texture.width = GetScreenWidth();
        renderTarget.texture.height = (float)renderTarget.texture.width * ((float)targetHeight / (float)targetWidth);
    }

    scaleHangover = (GetScreenWidth() - (int)renderTarget.texture.width) % 2;
    renderTarget.texture.width += scaleHangover;

    return (Rectangle){static_cast<float>((GetScreenWidth() - renderTarget.texture.width) / 2),
                       static_cast<float>((GetScreenHeight() - renderTarget.texture.height) / 2),
                       static_cast<float>(renderTarget.texture.width),
                       static_cast<float>(renderTarget.texture.height)};
}

Rectangle Screen2DManager::alternativeCalculateScaledRectangle(RenderTexture2D renderTarget,
                                                               int targetWidth,
                                                               int targetHeight)
{
    const float zoomLevel = 2.0f; // Define the zoom level

    // Set a new height and calculate the corresponding width while maintaining aspect ratio
    float newHeight = 500 * zoomLevel; // Set the desired height with zoom
    float aspectRatio = static_cast<float>(targetWidth) / static_cast<float>(targetHeight);
    renderTarget.texture.height = newHeight;
    renderTarget.texture.width = newHeight * aspectRatio; // Calculate width based on the new height

    int scaleHangover = 0;

    // Check if the calculated width exceeds the screen width
    if (renderTarget.texture.width > GetScreenWidth())
    {
        renderTarget.texture.width = GetScreenWidth(); // Clamp width to screen width
        renderTarget.texture.height =
            renderTarget.texture.width / aspectRatio; // Adjust height to maintain aspect ratio
    }

    // Calculate any hangover to ensure width is even
    scaleHangover = (GetScreenWidth() - static_cast<int>(renderTarget.texture.width)) % 2;
    renderTarget.texture.width += scaleHangover;

    // Calculate the position for lower-left corner
    float posX = 0;                                               // Align to the left edge of the screen
    float posY = GetScreenHeight() - renderTarget.texture.height; // Align to the bottom of the screen

    // Return the rectangle with the new position and adjusted dimensions
    return (Rectangle){posX,
                       posY,
                       static_cast<float>(renderTarget.texture.width),
                       static_cast<float>(renderTarget.texture.height)};
}
