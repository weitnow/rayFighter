#include <iostream>
#include "raylib.h"
#include "Characters/Fighter_Andi.h"
#include "Utils/AsepriteManager.h"
#include "Constants.h"

Rectangle CalculateScaledRectangle(RenderTexture2D target, int gameScreenWidth, int gameScreenHeight);


//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialize window
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1920;
    const int screenHeight = 1080;
    InitWindow(screenWidth, screenHeight, "C++ gbFighter");

    // Camera2D
    Camera2D camera = {0};
    camera.target = Vector2{0.0f, 0.0f};
    camera.offset = Vector2 {0.0f, 0.0f};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    // Create a RenderTexture2D to be used for render to texture
    const int gameScreenWidth = 960;
    const int gameScreenHeight = 540;
    RenderTexture2D target = LoadRenderTexture(gameScreenWidth, gameScreenHeight);

    // Setup the viewport rectangle properly scaled
    Rectangle scaledRec;

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    AsepriteManager asepriteManager{"Assets/Graphics/"};
    asepriteManager.loadAnimFile("gbFighter");
    asepriteManager.showLoadedAnimFiles();


    auto* player1 = new Fighter_Andi(200, 200);
    player1->setScale(4, 4);

    auto* player2 = new BaseGameObject(500, 500);
    player2->setScale(4, 4);




    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        float deltaTime = GetFrameTime();

        // Assign calculated result from function to scaledRec
        scaledRec = CalculateScaledRectangle(target, gameScreenWidth, gameScreenHeight);

        //----------------------------------------------------------------------------------
        // Update
        //----------------------------------------------------------------------------------
        player1->update(deltaTime);
        player2->update(deltaTime);


        // Camera rotation controls
        if(IsKeyDown(KEY_W)) camera.rotation--;
        else if(IsKeyDown(KEY_S)) camera.rotation++;

        // Camera zoom controls
        if(IsKeyDown(KEY_I)) camera.zoom += 0.01f;
        if(IsKeyDown(KEY_U)) camera.zoom -= 0.01f;

        // Camera x controls
        if(IsKeyDown(KEY_A)) camera.target.x--;
        if(IsKeyDown(KEY_D)) camera.target.x++;

        //----------------------------------------------------------------------------------
        // Draw to RenderTexture
        //----------------------------------------------------------------------------------
        BeginTextureMode(target);

        ClearBackground(RAYWHITE);


        BeginMode2D(camera);

        player1->draw();
        player2->draw();


        EndMode2D();



        DrawText("This is the Rendertarget", 190, 200, 20, LIGHTGRAY);

        EndTextureMode();


        //----------------------------------------------------------------------------------
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);



        DrawText("Using [A]/[S] to change camera rotation", 10, 10+30, 20, BLACK);
        DrawText("Using [Z]/[X] to change camera zoom", 10, 40+30, 20, BLACK);

        // Draw RenderTexture to Screen
        DrawTexturePro(target.texture, (Rectangle){ 0.0f, 0.0f, (float)target.texture.width, (float)-target.texture.height }, scaledRec, (Vector2){ 0, 0 }, 0.0f, WHITE);
        #ifdef DEBUG
            DrawFPS(10, 10);
        #endif

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}


// Function to calculate scaled rectangle dimensions
Rectangle CalculateScaledRectangle(RenderTexture2D target, int gameScreenWidth, int gameScreenHeight) {
    target.texture.height = GetScreenHeight();
    target.texture.width = (float)target.texture.height*((float)gameScreenWidth/(float)gameScreenHeight);
    int scaleHangover = 0;

    if (target.texture.width > GetScreenWidth())
    {
        target.texture.width = GetScreenWidth();
        target.texture.height = (float)target.texture.width*((float)gameScreenHeight/(float)gameScreenWidth);
    }

    scaleHangover = (GetScreenWidth() - (int)target.texture.width) % 2;
    target.texture.width += scaleHangover;

    return (Rectangle){ static_cast<float>((GetScreenWidth() - target.texture.width)/2), static_cast<float>((GetScreenHeight() - target.texture.height)/2), static_cast<float>(target.texture.width), static_cast<float>(target.texture.height) };
}