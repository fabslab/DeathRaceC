#pragma once

#include "IPlayerInput.h"
#include <vector>

class AggregatedPlayerInput : public IPlayerInput {
public:
    ~AggregatedPlayerInput() override = default;

    float GetThrottleValue() override;
    float GetDirection() override;

    void SetInputs(std::vector<IPlayerInput*> inputs);

private:
    std::vector<IPlayerInput*> inputs;
};
