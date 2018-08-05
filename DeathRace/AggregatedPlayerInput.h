#pragma once

#include "PlayerInput.h"
#include <vector>

class AggregatedPlayerInput : public PlayerInput {
public:
    AggregatedPlayerInput(std::vector<PlayerInput*> inputs);
    ~AggregatedPlayerInput() override;

    float GetThrottleValue() override;
    float GetDirection() override;

private:
    std::vector<PlayerInput*> inputs;
};
