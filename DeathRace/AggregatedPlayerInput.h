#pragma once

#include "ControllerPlayerInput.h"
#include "IPlayerInput.h"
#include "InputCommand.h"
#include "KeyboardPlayerInput.h"
#include <unordered_set>

class AggregatedPlayerInput : public IPlayerInput {
public:
    ~AggregatedPlayerInput() override = default;
    float GetThrottleValue() override;
    float GetDirection() override;
    void SetInputs(std::unordered_set<IPlayerInput*> inputs);
    bool WasCommandEntered(Input::InputCommand command);

private:
    std::unordered_set<IPlayerInput*> inputs;
    KeyboardPlayerInput *keyboardInputLeft, *keyboardInputRight;
    ControllerPlayerInput *controllerInputOne, *controllerInputTwo;
};
