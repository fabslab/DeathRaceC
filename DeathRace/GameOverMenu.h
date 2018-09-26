#pragma once

#include "Button.h"
#include "ButtonArea.h"
#include "IMenu.h"

class GameOverMenu : IMenu {
public:
    GameOverMenu();
    ~GameOverMenu();
    void Update(ECS::World* world) override;
    void Draw();

private:
    const char* scoreText[4][2] = {
        { "1-3", " POINTS: SKELETON CHASER" },
        { "4-10", " POINTS: BONE CRACKER" },
        { "11-20", " POINTS: GREMLIN HUNTER" },
        { "21", " or OVER: EXPERT DRIVER" }
    };
    Button* mainMenuButton;
    Button* exitButton;
    ButtonArea buttonArea;
};
