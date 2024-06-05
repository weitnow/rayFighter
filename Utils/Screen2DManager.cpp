//
// Created by weitnow on 12/26/23.
//

#include "Screen2DManager.h"

Screen2DManager::Screen2DManager(const int screenWidth, const int screenHeight, const char *windowTitle, const bool windowResizable)
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
    for (auto &pair : renderTargets)
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

    // Camera x controls
    if (IsKeyDown(KEY_A))
        camera.target.x--;
    if (IsKeyDown(KEY_D))
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
    scaledRectangle = calculateScaledRectangle(renderTarget, renderTarget.texture.width, renderTarget.texture.height);
    DrawTexturePro(renderTarget.texture, (Rectangle){0.0f, 0.0f, (float)renderTarget.texture.width, (float)-renderTarget.texture.height}, scaledRectangle, (Vector2){0, 0}, 0.0f, WHITE);
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

    return (Rectangle){static_cast<float>((GetScreenWidth() - renderTarget.texture.width) / 2), static_cast<float>((GetScreenHeight() - renderTarget.texture.height) / 2), static_cast<float>(renderTarget.texture.width), static_cast<float>(renderTarget.texture.height)};
}
