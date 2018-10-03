#pragma once

#include "IPlayerInput.h"
#include "KeyboardInputMap.h"
#include <unordered_map>

class KeyboardPlayerInput : public IPlayerInput {
public:
    KeyboardPlayerInput(Input::KeyboardInputMap inputMap);
    ~KeyboardPlayerInput() override = default;
    float GetThrottleValue() override;
    float GetDirection() override;
    bool WasCommandEntered(Input::InputCommand command) override;

private:
    Input::KeyboardInputMap inputMap;
};
