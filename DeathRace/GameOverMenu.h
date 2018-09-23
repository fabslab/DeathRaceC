#pragma once

#include "Button.h"
#include "ButtonArea.h"

class GameOverMenu {
public:
    GameOverMenu();
    ~GameOverMenu();
    void Update();
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
