#include "GameOverMenu.h"
#include "ControllerInputMap.h"
#include "Events.h"
#include "Fonts.h"
#include "GameConstants.h"
#include "GraphicsUtil.h"
#include "InputCommand.h"
#include "raylib.h"

GameOverMenu::GameOverMenu()
{
    float buttonSeparation = 10.f;

    mainMenuButton = new Button("MAIN MENU");
    float buttonsX = GameConstants::VIRTUAL_WIDTH / 2 - mainMenuButton->width / 2;
    float buttonsY = 178.f;
    mainMenuButton->SetPosition(Vector2{ buttonsX, buttonsY });

    buttonsY += mainMenuButton->height + buttonSeparation;
    exitButton = new Button("EXIT");
    exitButton->SetPosition(Vector2{ buttonsX, buttonsY });

    buttonArea = new ButtonArea(MenuOrientation::Vertical, { mainMenuButton, exitButton });
}

GameOverMenu::~GameOverMenu()
{
    delete mainMenuButton;
    delete exitButton;
}

void GameOverMenu::Update(ECS::World* world)
{
    buttonArea->Update();

    if (inputAggregator.WasCommandEntered(Input::InputCommand::Enter)) {
        Button* selectedButton = buttonArea->GetFocusedButton();
        if (selectedButton == mainMenuButton) {
            world->emit(Events::GameStateChangedEvent{ GameState::MainMenu });
            buttonArea->ResetFocus();
        } else if (selectedButton == exitButton) {
            world->emit(Events::GameStateChangedEvent{ GameState::Exit });
        }
    }
}

void GameOverMenu::Draw()
{
    float yPos = GameConstants::VIRTUAL_HEIGHT / 2 - 60;
    float fontSize = 12.f;
    float letterSpacing = 0.f;
    for (auto text : scoreText) {
        // Using two different font variations to render text due to rendering issues with letter E in main font
        Vector2 textSize1 = GraphicsUtil::MeasureText(Fonts::defaultFont12px, text[0], fontSize, letterSpacing);
        Vector2 textSize2 = GraphicsUtil::MeasureText(Fonts::defaultFont12pxEdit, text[1], fontSize, letterSpacing);
        float textX = GameConstants::VIRTUAL_WIDTH / 2 - (textSize1.x + textSize2.x) / 2;
        GraphicsUtil::DrawText(Fonts::defaultFont12px, text[0], Vector2{ textX, yPos }, fontSize, letterSpacing);
        GraphicsUtil::DrawText(Fonts::defaultFont12pxEdit, text[1], Vector2{ textX + textSize1.x, yPos }, fontSize, letterSpacing);
        yPos += Fonts::defaultFont12px.baseSize;
    }

    buttonArea->Draw();
}
