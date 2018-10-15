#include "GameOverMenu.h"
#include "Events.h"
#include "Fonts.h"
#include "GameConstants.h"
#include "GraphicsUtil.h"
#include "InputCommand.h"
#include "raylib.h"
#include "raymath.h"

GameOverMenu::GameOverMenu()
{
    float buttonSeparation = 10.f;

    mainMenuButton = new Button("MAIN MENU");
    float buttonsX = GameConstants::VIRTUAL_WIDTH / 2 - mainMenuButton->width / 2;
    float buttonsY = 178.f;
    mainMenuButton->SetPosition(Vector2 { buttonsX, buttonsY });

    buttonsY += mainMenuButton->height + buttonSeparation;
    exitButton = new Button("EXIT");
    exitButton->SetPosition(Vector2 { buttonsX, buttonsY });

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
            world->emit(Events::GameStateChangedEvent { GameState::MainMenu });
            buttonArea->ResetFocus();
        } else if (selectedButton == exitButton) {
            world->emit(Events::GameStateChangedEvent { GameState::Exit });
        }
    }

    if (highlightBrightness >= brightnessAnimationRange[0] && highlightBrightness <= brightnessAnimationRange[1]) {
        highlightBrightness += highlightAnimationDirection * .015;
    } else {
        highlightAnimationDirection *= -1;
        highlightBrightness = Clamp(highlightBrightness, brightnessAnimationRange[0], brightnessAnimationRange[1]);
    }
}

void GameOverMenu::Draw()
{
    float yPos = GameConstants::VIRTUAL_HEIGHT / 2 - 60;
    float fontSize = 12.f;
    float letterSpacing = 0.f;
    int index = 0;
    for (auto text : scoreText) {
        bool isLineHighlighted = highlightedRanges[index];
        Color lineColor = isLineHighlighted ? Fade(WHITE, highlightBrightness) : Fade(WHITE, .5f);
        // Using two different font variations to render text due to rendering issues with letter E in main font
        Vector2 textSize1 = GraphicsUtil::MeasureText(Fonts::defaultFont12px, text[0], fontSize, letterSpacing);
        Vector2 textSize2 = GraphicsUtil::MeasureText(Fonts::defaultFont12pxEdit, text[1], fontSize, letterSpacing);
        float textX = GameConstants::VIRTUAL_WIDTH / 2 - (textSize1.x + textSize2.x) / 2;
        GraphicsUtil::DrawText(Fonts::defaultFont12px, text[0], Vector2 { textX, yPos }, fontSize, letterSpacing, lineColor);
        GraphicsUtil::DrawText(Fonts::defaultFont12pxEdit, text[1], Vector2 { textX + textSize1.x, yPos }, fontSize, letterSpacing, lineColor);
        yPos += Fonts::defaultFont12px.baseSize;
        index++;
    }

    buttonArea->Draw();
}

void GameOverMenu::SetPlayerScores(std::vector<int> scores)
{
    highlightedRanges.assign(scoreRanges.size(), false);
    for (int score : scores) {
        for (size_t i = scoreRanges.size(); i > 0; --i) {
            if (score >= scoreRanges[i - 1]) {
                highlightedRanges[i - 1] = true;
                break;
            }
        }
    }
}
