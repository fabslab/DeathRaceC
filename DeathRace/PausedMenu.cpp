#include "PausedMenu.h"
#include "GameConstants.h"

PausedMenu::PausedMenu()
{
    float buttonWidth = 120.f;
    float buttonHeight = 30.f;
    float buttonSeparation = 10.f;
    float buttonsX = GameConstants::VIRTUAL_WIDTH / 2 - buttonWidth / 2;
    float buttonsY = GameConstants::VIRTUAL_HEIGHT / 2 - (buttonHeight * 3 + 2 * buttonSeparation) / 2;

    resumeButton = new Button(buttonsX, buttonsY, buttonWidth, buttonHeight, "RESUME");
    buttonsY += buttonHeight + buttonSeparation;
    mainMenuButton = new Button(buttonsX, buttonsY, buttonWidth, buttonHeight, "MAIN MENU");
    buttonsY += buttonHeight + buttonSeparation;
    exitButton = new Button(buttonsX, buttonsY, buttonWidth, buttonHeight, "EXIT");

    buttonArea = ButtonArea(MenuOrientation::Vertical, { resumeButton, mainMenuButton, exitButton });
}

PausedMenu::~PausedMenu()
{
    delete resumeButton;
    delete mainMenuButton;
    delete exitButton;
}

void PausedMenu::Update()
{
    buttonArea.Update();
}

void PausedMenu::Draw()
{
    buttonArea.Draw();
}
