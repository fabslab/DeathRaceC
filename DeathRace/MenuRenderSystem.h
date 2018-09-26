#pragma once

#include "ECS.h"
#include "GameOverMenu.h"
#include "MainMenu.h"
#include "PausedMenu.h"

class MenuRenderSystem : public ECS::EntitySystem {
public:
    MenuRenderSystem();
    virtual void tick(ECS::World* world, float deltaTime) override;

private:
    GameOverMenu gameOverMenu;
    PausedMenu pausedMenu;
    MainMenu mainMenu;
};
