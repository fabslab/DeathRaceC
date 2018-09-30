#pragma once

#include "AggregatedPlayerInput.h"
#include "ECS.h"
#include "KeyboardPlayerInput.h"
#include "PlayerIndex.h"
#include "PlayerMovementCommand.h"
#include "raylib.h"
#include <array>
#include <vector>

class PlayerMovementSystem : public ECS::EntitySystem {
public:
    PlayerMovementSystem();
    virtual ~PlayerMovementSystem();
    virtual void tick(ECS::World* world, float deltaTime) override;
    void SetCommandBuffers(std::array<std::vector<PlayerMovementCommand>, 2>& buffer);
    std::array<std::vector<PlayerMovementCommand>, 2> GetCommandBuffers();
    void ClearCommandBuffers();
    void SetNumPlayers(int numPlayers);

private:
    void UpdateEngineIdleSound();
    void UpdateEngineRunningSound(PlayerIndex playerIndex, float throttle);
    AggregatedPlayerInput inputAggregator;
    KeyboardPlayerInput *keyboardInputLeft, *keyboardInputRight;
    std::array<std::vector<PlayerMovementCommand>, 2> movementCommandBuffer;
    int numPlayers = 0;
    Music engineIdleSound = nullptr;
    Music playerEngineSounds[2] = { nullptr, nullptr };
    float playerEngineVolumes[2] = { 0.f, 0.f };
};
