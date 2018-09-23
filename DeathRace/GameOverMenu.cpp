#include "GameOverMenu.h"
#include "Fonts.h"
#include "GameConstants.h"
#include "GraphicsUtil.h"

GameOverMenu::GameOverMenu()
{
    float buttonWidth = 120.f;
    float buttonHeight = 30.f;
    float buttonSeparation = 10.f;
    float buttonsX = GameConstants::VIRTUAL_WIDTH / 2 - buttonWidth / 2;
    float buttonsY = 178.f;

    mainMenuButton = new Button(buttonsX, buttonsY, buttonWidth, buttonHeight, "MAIN MENU");
    buttonsY += buttonHeight + buttonSeparation;
    exitButton = new Button(buttonsX, buttonsY, buttonWidth, buttonHeight, "EXIT");

    buttonArea = ButtonArea(MenuOrientation::Vertical, { mainMenuButton, exitButton });
}

GameOverMenu::~GameOverMenu()
{
    delete mainMenuButton;
    delete exitButton;
}

void GameOverMenu::Update()
{
    buttonArea.Update();
}

void GameOverMenu::Draw()
{
    float yPos = GameConstants::VIRTUAL_HEIGHT / 2 - 60;
    float fontSize = 12.f;
    for (auto text : scoreText) {
        // Using two different font variations to render text due to rendering issues with letter E in main font
        Vector2 textSize1 = GraphicsUtil::MeasureText(Fonts::defaultFont12px, text[0], fontSize, 0);
        Vector2 textSize2 = GraphicsUtil::MeasureText(Fonts::defaultFont12pxEdit, text[1], fontSize, 0);
        float textX = GameConstants::VIRTUAL_WIDTH / 2 - (textSize1.x + textSize2.x) / 2;
        GraphicsUtil::DrawText(Fonts::defaultFont12px, text[0], Vector2{ textX, yPos }, fontSize, 0);
        GraphicsUtil::DrawText(Fonts::defaultFont12pxEdit, text[1], Vector2{ textX + textSize1.x, yPos }, fontSize, 0);
        yPos += Fonts::defaultFont12px.baseSize;
    }

    buttonArea.Draw();
}
