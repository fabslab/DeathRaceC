#pragma once

#include "AggregatedPlayerInput.h"
#include "ECS.h"
#include "KeyboardPlayerInput.h"
#include "MovementCommand.h"
#include <array>
#include <vector>

class PlayerMovementSystem : public ECS::EntitySystem {
public:
    PlayerMovementSystem();
    virtual ~PlayerMovementSystem();
    virtual void tick(ECS::World* world, float deltaTime) override;
    void SetCommandBuffers(std::array<std::vector<MovementCommand>, 2>& buffer);
    std::array<std::vector<MovementCommand>, 2> GetCommandBuffers();
    void ClearCommandBuffers();
    void SetNumPlayers(int numPlayers);

private:
    AggregatedPlayerInput inputAggregator;
    KeyboardPlayerInput *keyboardInputLeft, *keyboardInputRight;
    std::array<std::vector<MovementCommand>, 2> movementCommandBuffer;
    int numPlayers = 0;
};
