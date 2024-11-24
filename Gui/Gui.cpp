#include "Gui.h"
#include "../Game/Game.h"

Gui::Gui(Game* game) : game(game)
{
    lifebar1 =
        new Lifebar(Vector2{23, 26}, 5, 100, 3, Constants::RAYFIGHTER_ROSA, Constants::RAYFIGHTER_LIGHTROSA, "Andy", 1);
    lifebar2 = new Lifebar(Vector2{132, 26},
                           5,
                           100,
                           3,
                           Constants::RAYFIGHTER_ROSA,
                           Constants::RAYFIGHTER_LIGHTROSA,
                           "Zangief",
                           2);


    //Load the bgUpperGui animation
    bgUpperGui = game->asepriteManager->getAnimFile("bgUpperGui");
    bgUpperGui->setFrameTag("bgUpperGui-Idle");

    //Load the bgLowerGui animation
    bgLowerGui = game->asepriteManager->getAnimFile("bgLowerGui");
    bgLowerGui->setFrameTag("bgLowerGui-Idle");
}

Gui::~Gui()
{
    // Clean up resources if necessary
    delete lifebar1;
    delete lifebar2;
    lifebar1 = nullptr;
    lifebar2 = nullptr;

    delete bgUpperGui;
    delete bgLowerGui;
}

void Gui::draw()
{
    // Draw a white rectangle for UpperGui
    DrawRectangle(0, 0, 256, 40, BLACK);

    // Draw the lifebars
    lifebar1->Draw();
    lifebar2->Draw();

    // Draw the bgUpperGui
    bgUpperGui->drawCurrentSelectedTag(0, 0, 1, WHITE);

    DrawText("99", 122, 11, 8, Constants::RAYFIGHTER_LIGHTROSA);

    // Draw a white rectangle for LowerGui
    DrawRectangle(0, 136, 256, 8, BLACK);

    // Draw the bgLowerGui
    bgLowerGui->drawCurrentSelectedTag(0, 136, 1, WHITE);
}

void Gui::update(float deltaTime)
{
    // Update the bgUpperGui
    bgUpperGui->update(deltaTime);

    // Update the bgLowerGui
    bgLowerGui->update(deltaTime);
}

void Gui::setLife1(int life)
{
    lifebar1->Update(life);
}

void Gui::setLife2(int life)
{
    lifebar2->Update(life);
}
