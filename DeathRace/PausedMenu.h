#pragma once

#include "Button.h"
#include "ButtonArea.h"
#include "ECS.h"
#include "IMenu.h"

class PausedMenu : IMenu {
public:
    PausedMenu();
    ~PausedMenu();
    void Update(ECS::World* world) override;
    void Draw();

private:
    Button* resumeButton;
    Button* mainMenuButton;
    Button* exitButton;
    ButtonArea buttonArea;
};
