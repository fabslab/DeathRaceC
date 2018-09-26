#pragma once

#include "Button.h"
#include "ButtonArea.h"
#include "IMenu.h"

class MainMenu : IMenu {
public:
    MainMenu();
    ~MainMenu();
    void Update(ECS::World* world) override;
    void Draw() override;

private:
    const char* instructionsText[3] = {
        "HIT GREMLINS FOR POINTS",
        "USE REVERSE FOR QUICKER",
        "GETAWAY AFTER CRASH",
    };
    Button* onePlayerButton;
    Button* twoPlayersButton;
    ButtonArea buttonArea;
};
