#include "MainMenu.h"
#include "Events.h"
#include "Fonts.h"
#include "GameConstants.h"
#include "GameState.h"
#include "GraphicsUtil.h"
#include "Scene.h"
#include "Textures.h"
#include "raylib.h"

MainMenu::MainMenu()
{
    onePlayerButton = new Button("1 PLAYER");
    twoPlayersButton = new Button("2 PLAYERS");

    float buttonSpacing = 20.f;
    float buttonWidth = onePlayerButton->width;
    float buttonsWidth = 2 * buttonWidth + buttonSpacing;
    float buttonsX = GameConstants::VIRTUAL_WIDTH / 2 - buttonsWidth / 2;
    float buttonsY = Textures::marquee.height + 20.f;
    onePlayerButton->SetPosition(Vector2{ buttonsX, buttonsY });
    twoPlayersButton->SetPosition(Vector2{ buttonsX + buttonWidth + buttonSpacing, buttonsY });

    buttonArea = ButtonArea(MenuOrientation::Horizontal, { onePlayerButton, twoPlayersButton });
}

MainMenu::~MainMenu()
{
    delete onePlayerButton;
    delete twoPlayersButton;
}

void MainMenu::Update(ECS::World* world)
{
    buttonArea.Update();

    if (IsKeyPressed(KEY_ENTER)) {
        Button* selectedButton = buttonArea.GetFocusedButton();
        if (selectedButton == onePlayerButton) {
            Scene::SetCurrentScene(new Scene(world, 1));
        } else if (selectedButton == twoPlayersButton) {
            Scene::SetCurrentScene(new Scene(world, 2));
        }
        world->emit(Events::GameStateChangedEvent{ GameState::GameRunning });
    }
}

void MainMenu::Draw()
{
    float marqueeX = GameConstants::VIRTUAL_WIDTH / 2;
    float marqueeY = Textures::marquee.height / 2 + 10.f;
    GraphicsUtil::DrawTexture(Textures::marquee, Vector2{ marqueeX, marqueeY });
    buttonArea.Draw();

    float yPos = onePlayerButton->y + onePlayerButton->height + 12.f;
    float fontSize = 12.f;
    float letterSpacing = 0.f;
    for (auto text : instructionsText) {
        // Using two different font variations to render text due to rendering issues with letter E in main font
        Vector2 textSize = GraphicsUtil::MeasureText(Fonts::defaultFont12px, text, fontSize, letterSpacing);
        float textX = GameConstants::VIRTUAL_WIDTH / 2 - textSize.x / 2;
        GraphicsUtil::DrawText(Fonts::defaultFont12pxEdit, text, Vector2{ textX, yPos }, fontSize, letterSpacing);
        yPos += Fonts::defaultFont12px.baseSize;
    }
}
