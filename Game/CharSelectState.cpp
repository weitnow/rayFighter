#include "CharSelectState.h"
#include "Game.h"
#include "GameState.h"


CharSelectState::CharSelectState(Game* game) : BaseState(game), CharSelectScreen(nullptr)
{
    CharSelectScreen = game->asepriteManager->getAnimFile("charSelectScreen");
    CharSelectScreen->setFrameTag("charSelectScreen-Idle");
}

CharSelectState::~CharSelectState()
{

    std::cout << "CharSelectState Destructor called, unloading resources" << std::endl;

    if (Constants::BACKGROUND_MUSIC)
    {
        game->soundManager->unloadMusic("warriormonk.mp3");
    }


    delete CharSelectScreen;
}

void CharSelectState::Enter()
{
    BaseState::Enter();

    // Start playing background music
    if (Constants::BACKGROUND_MUSIC)
    {
        game->soundManager->loadMusic("warriormonk.mp3", 1.f);
        game->soundManager->playBackgroundMusic("warriormonk.mp3");
    }

    // Adding characters
    characters = {{{82, 30, 28, 28}, "Character 1"},
                  {{114, 30, 28, 28}, "Character 2"},
                  {{146, 30, 28, 28}, "Character 3"}};

    // Adding stages
    stages = {{{50, 300, 100, 100}, "Stage 1"}, {{200, 300, 100, 100}, "Stage 2"}, {{350, 300, 100, 100}, "Stage 3"}};
}

void CharSelectState::Update(float deltaTime)
{
    game->soundManager->updateBackgroundMusic(); // Update Music

    //handle input //todo: refactor this to inputHandler
    if (IsKeyPressed(KEY_ENTER))
    {

        game->ChangeState(std::make_unique<GameState>(game));
    }
    if (IsKeyPressed(KEY_D))
    {
        if (selectingCharacter)
        {
            selectedCharacter = (selectedCharacter + 1) % characters.size();
        }
        else
        {
            selectedStage = (selectedStage + 1) % stages.size();
        }
    }
    else if (IsKeyPressed(KEY_A))
    {
        if (selectingCharacter)
        {
            selectedCharacter = (selectedCharacter - 1 + characters.size()) % characters.size();
        }
        else
        {
            selectedStage = (selectedStage - 1 + stages.size()) % stages.size();
        }
    }
    else if (IsKeyPressed(KEY_SPACE))
    {
        selectingCharacter = !selectingCharacter; // Toggle between character and stage
    }
}

void CharSelectState::Render()
{
    //----------------------------------------------------------------------------------
    // Draw to RenderTexture
    //----------------------------------------------------------------------------------
    game->screen2DManager->beginDrawToRenderTarget();

    ClearBackground(GREEN);

    // Draw CharSelectScreen
    CharSelectScreen->drawCurrentSelectedTag(0, 0);

    if (selectingCharacter)
    {
        DrawSelectionScreen(characters, selectedCharacter, "Select Character");
    }
    else
    {
        DrawSelectionScreen(stages, selectedStage, "Select Stage");
    }


    game->screen2DManager->endDrawToRenderTarget();


    //----------------------------------------------------------------------------------
    // Draw to Screen
    //----------------------------------------------------------------------------------
    game->screen2DManager->beginDrawToScreen();

    // Draw RenderTexture to Screen
    game->screen2DManager->drawRenderTarget();

    game->screen2DManager->endDrawToScreen();
}


void CharSelectState::Exit()
{
}

void CharSelectState::DrawSelectionScreen(const List<Option>& options, int selectedIndex, const char* title)
{
    DrawText(title, 8, 8, 8, BLACK);

    for (size_t i = 0; i < options.size(); ++i)
    {
        Color color = (i == selectedIndex) ? YELLOW : GRAY;
        //DrawRectangleRec(options[i].rect, color);
        DrawRectangleLinesEx(options[i].rect, 1.0f, color);
        //DrawText(options[i].name.c_str(), options[i].rect.x + 10, options[i].rect.y + 10, 8, BLACK);
    }
}
