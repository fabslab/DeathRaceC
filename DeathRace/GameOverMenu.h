#pragma once

#include "Button.h"
#include "ButtonArea.h"
#include "Menu.h"

class GameOverMenu : Menu {
public:
    GameOverMenu();
    ~GameOverMenu() override;
    void Update(ECS::World* world) override;
    void Draw() override;

private:
    const char* scoreText[4][2] = {
        { "1-3", " POINTS: SKELETON CHASER" },
        { "4-10", " POINTS: BONE CRACKER" },
        { "11-20", " POINTS: GREMLIN HUNTER" },
        { "21", " or OVER: EXPERT DRIVER" }
    };
    ButtonArea* buttonArea;
    Button* mainMenuButton;
    Button* exitButton;
};
