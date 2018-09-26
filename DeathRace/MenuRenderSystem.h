#pragma once

#include "ECS.h"
#include "Events.h"
#include "GameOverMenu.h"
#include "GameState.h"
#include "MainMenu.h"
#include "PausedMenu.h"

class MenuRenderSystem : public ECS::EntitySystem, public ECS::EventSubscriber<Events::GameStateChangedEvent> {
public:
    virtual void configure(ECS::World* world) override;
    virtual void unconfigure(ECS::World* world) override;
    virtual void receive(ECS::World* world, const Events::GameStateChangedEvent& event) override;
    virtual void tick(ECS::World* world, float deltaTime) override;

private:
    GameOverMenu gameOverMenu;
    PausedMenu pausedMenu;
    MainMenu mainMenu;
    GameState gameState;
};
