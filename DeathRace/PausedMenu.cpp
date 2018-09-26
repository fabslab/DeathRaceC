#include "PausedMenu.h"
#include "GameConstants.h"

PausedMenu::PausedMenu()
{
    float buttonSeparation = 10.f;

    resumeButton = new Button("RESUME");
    float buttonsX = GameConstants::VIRTUAL_WIDTH / 2 - resumeButton->width / 2;
    float buttonsY = GameConstants::VIRTUAL_HEIGHT / 2 - (resumeButton->height * 3 + 2 * buttonSeparation) / 2;
    resumeButton->SetPosition(Vector2{ buttonsX, buttonsY });

    buttonsY += resumeButton->height + buttonSeparation;
    mainMenuButton = new Button("MAIN MENU");
    mainMenuButton->SetPosition(Vector2{ buttonsX, buttonsY });

    buttonsY += mainMenuButton->height + buttonSeparation;
    exitButton = new Button("EXIT");
    exitButton->SetPosition(Vector2{ buttonsX, buttonsY });

    buttonArea = ButtonArea(MenuOrientation::Vertical, { resumeButton, mainMenuButton, exitButton });
}

PausedMenu::~PausedMenu()
{
    delete resumeButton;
    delete mainMenuButton;
    delete exitButton;
}

void PausedMenu::Update(ECS::World* world)
{
    buttonArea.Update();
}

void PausedMenu::Draw()
{
    buttonArea.Draw();
}
