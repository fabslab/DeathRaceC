#pragma once

#include "ControllerPlayerInput.h"
#include "IPlayerInput.h"
#include "InputCommand.h"
#include "KeyboardPlayerInput.h"
#include <vector>

class AggregatedPlayerInput : public IPlayerInput {
public:
    ~AggregatedPlayerInput() override = default;
    float GetThrottleValue() override;
    float GetDirection() override;
    bool WasCommandEntered(Input::InputCommand command) override;
    void SetInputs(std::vector<IPlayerInput*> inputs);

private:
    std::vector<IPlayerInput*> inputs;
};
