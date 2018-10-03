#pragma once

#include "Button.h"
#include "ButtonArea.h"
#include "ECS.h"
#include "Menu.h"

class PausedMenu : Menu {
public:
    PausedMenu();
    ~PausedMenu() override;
    void Update(ECS::World* world) override;
    void Draw() override;

private:
    ButtonArea* buttonArea;
    Button* resumeButton;
    Button* mainMenuButton;
    Button* exitButton;
};
