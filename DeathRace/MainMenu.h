#pragma once

#include "Button.h"
#include "ButtonArea.h"
#include "Menu.h"

class MainMenu : Menu {
public:
    MainMenu();
    ~MainMenu() override;
    void Update(ECS::World* world) override;
    void Draw() override;

private:
    const char* instructionsText[3] = {
        "HIT GREMLINS FOR POINTS",
        "USE REVERSE FOR QUICKER",
        "GETAWAY AFTER CRASH",
    };
    ButtonArea* buttonArea;
    Button* onePlayerButton;
    Button* twoPlayersButton;
};
