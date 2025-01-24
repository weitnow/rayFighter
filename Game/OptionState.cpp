#include "OptionState.h"
#include "../Constants.h"
#include "Game.h"
#include "GameState.h"

const char* resolutionOptions[] = {"640x480", "800x600", "1280x720", "1920x1080", "2560x1440", "3440x1440"};

OptionSelectState::OptionSelectState(Game* game) : BaseState(game), OptionSelectScreen(nullptr), selectedOption{0}
{
    OptionSelectScreen = game->asepriteManager->getAnimFile("optionSelectScreen");
    OptionSelectScreen->setFrameTag("optionSelectScreen-Intro");
}

OptionSelectState::~OptionSelectState()
{

    std::cout << "CharSelectState Destructor called, unloading resources" << std::endl;

    game->soundManager->unloadMusic("sunburn.mp3");

    delete OptionSelectScreen;
}

void OptionSelectState::Enter()
{
    BaseState::Enter();

    // Start playing background music
    game->soundManager->loadMusic("sunburn.mp3", 1.f);
    game->soundManager->playBackgroundMusic("sunburn.mp3");

    screen2DManager->fadeEffect(0.6f, 0.f);
}

void OptionSelectState::Update(float deltaTime)
{

    // Update OptionSelectScreen
    OptionSelectScreen->update(deltaTime);

    if (OptionSelectScreen->getCurrentFrame() == OptionSelectScreen->getMaxFrame())
    {
        OptionSelectScreen->setFrameTag("optionSelectScreen-Idle");
    }

    // Update Variables (Resolution, Music on/off, Mastervolume etc)


    HandleInput();
}

void OptionSelectState::Render()
{
    //----------------------------------------------------------------------------------
    // Draw to RenderTexture
    //----------------------------------------------------------------------------------
    game->screen2DManager->beginDrawToRenderTarget();

    ClearBackground(GREEN);

    // Draw OptionSelectScreen
    OptionSelectScreen->drawCurrentSelectedTag(0, 0);

    // Draw availabe Screenresolution
    _renderOptionMenu();

    screen2DManager->draw();

    game->screen2DManager->endDrawToRenderTarget();


    //----------------------------------------------------------------------------------
    // Draw to Screen
    //----------------------------------------------------------------------------------
    ClearBackground(BLACK);
    game->screen2DManager->beginDrawToScreen();

    // Draw RenderTexture to Screen
    game->screen2DManager->drawRenderTarget();

    // render overlay
    game->screen2DManager->drawOverlay();

    game->screen2DManager->endDrawToScreen();
}

void OptionSelectState::Pause()
{
}

void OptionSelectState::Resume()
{
}


void OptionSelectState::Exit()
{
}

void OptionSelectState::HandleInput()
{
    if (player1Controller->jump && inputHandler->isKeyJustPressed(*player1Controller)) // up
    {
        selectedRow.decrement();
    }
    else if (player1Controller->duck && inputHandler->isKeyJustPressed(*player1Controller)) // down
    {
        selectedRow.increment();
    }

    if (player1Controller->moveRight && inputHandler->isKeyJustPressed(*player1Controller)) // right
    {
        _selectOption(1);
    }
    else if (player1Controller->moveLeft && inputHandler->isKeyJustPressed(*player1Controller)) // left
    {
        _selectOption(-1);
    }


    if (player1Controller->kick)
    {
        //pop this state and return to menu
        game->PopState();
    }
    else if (player1Controller->punch || player2Controller->punch)
    {
        /* code */
    }
}

void OptionSelectState::_selectOption(int changeVal)
{
    // this function changes the value of selectedOption and makes sure that the value keeps between valid values
    selectedOption = Utils::calculate_circular_counter(selectedOption, changeVal, 0, _getMaxValOfSelectedOption());
}

int OptionSelectState::_getMaxValOfSelectedOption() //depends on the selectedRow
{
    switch (selectedRow.get_value())
    {
    case 0: //0 = Resolution
        return 5;
    case 1: // 1 = Music on/off,
        return 1;
    case 2: // 2 = Sound Master Volume
        return 9;
    case 3: // 3 = Input P1
        return 0;
    case 4: // 4 = Input P2
        return 0;
    default:
        return 0;
    }
}

void OptionSelectState::_renderOptionMenu()
{
    const int indentcol1 = 40;
    const int indentcol2 = 100;

    Color color = (selectedRow.get_value() == 0) ? Constants::RAYFIGHTER_WHITE : Constants::RAYFIGHTER_BLACK;
    DrawText("Resolution", indentcol1, 50, 8, color);
    DrawText(resolutionOptions[selectedOption], indentcol2, 50, 8, color);

    color = (selectedRow.get_value() == 1) ? Constants::RAYFIGHTER_WHITE : Constants::RAYFIGHTER_BLACK;
    DrawText("Music", indentcol1, 60, 8, color);

    color = (selectedRow.get_value() == 2) ? Constants::RAYFIGHTER_WHITE : Constants::RAYFIGHTER_BLACK;
    DrawText("Mastervolume", indentcol1, 70, 8, color);

    color = (selectedRow.get_value() == 3) ? Constants::RAYFIGHTER_WHITE : Constants::RAYFIGHTER_BLACK;
    DrawText("P1 Input", indentcol1, 80, 8, color);

    color = (selectedRow.get_value() == 4) ? Constants::RAYFIGHTER_WHITE : Constants::RAYFIGHTER_BLACK;
    DrawText("P2 Input", indentcol1, 90, 8, color);
}
