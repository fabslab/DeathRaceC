#pragma once

#include "AggregatedPlayerInput.h"
#include "ControllerPlayerInput.h"
#include "ECS.h"
#include "Events.h"
#include "GameOverMenu.h"
#include "GameState.h"
#include "MainMenu.h"
#include "PausedMenu.h"

class MenuRenderSystem : public ECS::EntitySystem, public ECS::EventSubscriber<Events::GameStateChangedEvent> {
public:
    void configure(ECS::World* world) override;
    void unconfigure(ECS::World* world) override;
    void receive(ECS::World* world, const Events::GameStateChangedEvent& event) override;
    void tick(ECS::World* world, float deltaTime) override;

private:
    GameOverMenu gameOverMenu;
    PausedMenu pausedMenu;
    MainMenu mainMenu;
    GameState gameState;
    AggregatedPlayerInput inputAggregator;
    KeyboardPlayerInput* keyboardInput;
    ControllerPlayerInput *controllerInputOne, *controllerInputTwo;
};
