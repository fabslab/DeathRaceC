#pragma once

#include "Button.h"
#include "ButtonArea.h"
#include "Menu.h"
#include <vector>

class GameOverMenu : Menu {
public:
    GameOverMenu();
    ~GameOverMenu() override;
    void Update(ECS::World* world) override;
    void Draw() override;
    void SetPlayerScores(std::vector<int> scores);

private:
    const char* scoreText[4][2] = {
        { "1-3", " POINTS: SKELETON CHASER" },
        { "4-10", " POINTS: BONE CRACKER" },
        { "11-20", " POINTS: GREMLIN HUNTER" },
        { "21", " or OVER: EXPERT DRIVER" }
    };
    std::vector<int> scoreRanges = { 1, 4, 11, 21 };
    std::vector<bool> highlightedRanges = { false, false, false, false };
    float highlightBrightness = 1.f;
    int highlightAnimationDirection = -1;
    float brightnessAnimationRange[2] = { .8f, 1.f };
    ButtonArea* buttonArea;
    Button* mainMenuButton;
    Button* exitButton;
};
