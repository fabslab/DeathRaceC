#pragma once

#include "AggregatedPlayerInput.h"
#include "ControllerPlayerInput.h"
#include "ECS.h"
#include "Events.h"
#include "KeyboardPlayerInput.h"
#include "PlayerIndex.h"
#include "raylib.h"
#include <array>
#include <vector>

class PlayerMovementSystem
    : public ECS::EntitySystem,
      public ECS::EventSubscriber<Events::CollisionEnteredEvent>,
      public ECS::EventSubscriber<Events::NumberOfPlayersChanged> {
public:
    void configure(ECS::World* world) override;
    void unconfigure(ECS::World* world) override;
    void receive(ECS::World* world, const Events::CollisionEnteredEvent& event) override;
    void receive(ECS::World* world, const Events::NumberOfPlayersChanged& event) override;
    void tick(ECS::World* world, float deltaTime) override;

private:
    void UpdateEngineIdleSound();
    void UpdateEngineRunningSound(PlayerIndex playerIndex, float throttle);
    void CrashPlayer(ECS::Entity* player);
    AggregatedPlayerInput inputAggregator;
    KeyboardPlayerInput* keyboardInputLeft = nullptr;
    KeyboardPlayerInput* keyboardInputRight = nullptr;
    ControllerPlayerInput* controllerInputOne = nullptr;
    ControllerPlayerInput* controllerInputTwo = nullptr;
    int numPlayers = 0;
    Music engineIdleSound = {};
    std::array<Music, 2> playerEngineSounds = { {}, {} };
    std::array<float, 2> playerEngineVolumes = { 0.f, 0.f };
};
