#include "PausedMenu.h"
#include "Events.h"
#include "GameConstants.h"
#include "GameState.h"

PausedMenu::PausedMenu()
{
    float buttonSeparation = 10.f;

    resumeButton = new Button("CONTINUE");
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

    if (IsKeyPressed(KEY_ENTER)) {
        Button* selectedButton = buttonArea.GetFocusedButton();
        if (selectedButton == resumeButton) {
            world->emit(Events::GameStateChangedEvent{ GameState::GameRunning });
        } else if (selectedButton == mainMenuButton) {
            world->emit(Events::GameStateChangedEvent{ GameState::MainMenu });
        } else if (selectedButton == exitButton) {
            world->emit(Events::GameStateChangedEvent{ GameState::Exit });
        }
    }
}

void PausedMenu::Draw()
{
    buttonArea.Draw();
}
