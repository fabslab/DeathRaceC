#pragma once

#include "Button.h"
#include "ButtonArea.h"

class PausedMenu {
public:
    PausedMenu();
    ~PausedMenu();
    void Update();
    void Draw();

private:
    Button* resumeButton;
    Button* mainMenuButton;
    Button* exitButton;
    ButtonArea buttonArea;
};
