#include "Hud.h"
#include "../Utils/GameManager.h"

Hud::Hud()
{
    lifebar1 =
        new Lifebar(Vector2{22, 17}, 6, 96, 3, Constants::RAYFIGHTER_ROSA, Constants::RAYFIGHTER_DARKBROWN, "Andy", 1);
    lifebar2 = new Lifebar(Vector2{132, 26},
                           5,
                           100,
                           3,
                           Constants::RAYFIGHTER_ROSA,
                           Constants::RAYFIGHTER_DARKBROWN,
                           "Zangief",
                           2);

    specialmeter1 =
        new Lifebar(Vector2{48, 25}, 4, 72, 3, Constants::RAYFIGHTER_ROSA, Constants::RAYFIGHTER_DARKBROWN, "", 1);

    specialmeter2 =
        new Lifebar(Vector2{132, 33}, 4, 100, 3, Constants::RAYFIGHTER_ROSA, Constants::RAYFIGHTER_DARKBROWN, "", 2);

    // Load the bgUpperGui animation
    //bgHUD = gameManager->getAsepriteManager()->getAnimFile("bgHUD");
    //bgHUD->setFrameTag("bgHUD-Idle");
}

Hud::~Hud()
{
    // Clean up resources if necessary
    delete lifebar1;
    delete lifebar2;
    lifebar1 = nullptr;
    lifebar2 = nullptr;

    delete specialmeter1;
    delete specialmeter2;
    specialmeter1 = nullptr;
    specialmeter2 = nullptr;
}

void Hud::Draw()
{
    // Draw the lifebars
    lifebar1->Draw();
    lifebar2->Draw();

    // Draw the specialmeters
    specialmeter1->Draw();
    specialmeter2->Draw();

    // Draw the bgUpperGui
    //bgHUD->drawCurrentSelectedTag(0, 0, 1, WHITE);

    DrawText("99", 122, 11, 8, Constants::RAYFIGHTER_DARKBROWN);
}

void Hud::Update(float deltaTime)
{


    // Update the bgUpperGui
    //bgHUD->update(deltaTime);
}

void Hud::setLife1(int life)
{
    lifebar1->Update(life);
}

void Hud::setLife2(int life)
{
    lifebar2->Update(life);
}

void Hud::setSpecial1(int special)
{
    specialmeter1->Update(special);
}

void Hud::setSpecial2(int special)
{
    specialmeter2->Update(special);
}
