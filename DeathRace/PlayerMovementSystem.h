#pragma once

#include "AggregatedPlayerInput.h"
#include "ControllerPlayerInput.h"
#include "ECS.h"
#include "Events.h"
#include "KeyboardPlayerInput.h"
#include "PlayerIndex.h"
#include "PlayerMovementCommand.h"
#include "raylib.h"
#include <array>
#include <vector>

class PlayerMovementSystem
    : public ECS::EntitySystem,
      public ECS::EventSubscriber<Events::CollisionEnteredEvent>,
      public ECS::EventSubscriber<Events::NumberOfPlayersChanged> {
public:
    virtual void configure(ECS::World* world) override;
    virtual void unconfigure(ECS::World* world) override;
    virtual void receive(ECS::World* world, const Events::CollisionEnteredEvent& event) override;
    virtual void receive(ECS::World* world, const Events::NumberOfPlayersChanged& event) override;
    virtual void tick(ECS::World* world, float deltaTime) override;
    void SetCommandBuffers(std::array<std::vector<PlayerMovementCommand>, 2>& buffer);
    std::array<std::vector<PlayerMovementCommand>, 2> GetCommandBuffers();
    void ClearCommandBuffers();

private:
    void UpdateEngineIdleSound();
    void UpdateEngineRunningSound(PlayerIndex playerIndex, float throttle);
    void CrashPlayer(ECS::Entity* player);
    AggregatedPlayerInput inputAggregator;
    KeyboardPlayerInput *keyboardInputLeft, *keyboardInputRight;
    ControllerPlayerInput *controllerInputOne, *controllerInputTwo;
    std::array<std::vector<PlayerMovementCommand>, 2> movementCommandBuffer;
    int numPlayers = 0;
    Music engineIdleSound = nullptr;
    Music playerEngineSounds[2] = { nullptr, nullptr };
    float playerEngineVolumes[2] = { 0.f, 0.f };
};
