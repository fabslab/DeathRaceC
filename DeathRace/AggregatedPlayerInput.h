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
    void SetInputs(std::vector<IPlayerInput*> inputs);
    bool WasCommandEntered(Input::InputCommand command);

private:
    std::vector<IPlayerInput*> inputs;
    KeyboardPlayerInput *keyboardInputLeft, *keyboardInputRight;
    ControllerPlayerInput *controllerInputOne, *controllerInputTwo;
};
