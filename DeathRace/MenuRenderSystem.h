#pragma once

#include "ECS.h"
#include "GameOverMenu.h"

class MenuRenderSystem : public ECS::EntitySystem {
public:
    MenuRenderSystem();
    virtual void tick(ECS::World* world, float deltaTime) override;

private:
    GameOverMenu gameOverMenu;
};
