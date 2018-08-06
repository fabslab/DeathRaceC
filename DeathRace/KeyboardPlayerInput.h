#pragma once

#include "KeyboardInputMap.h"
#include "PlayerInput.h"
#include <unordered_map>

class KeyboardPlayerInput : public PlayerInput {
public:
    KeyboardPlayerInput(Input::KeyboardInputMap inputMap);
    ~KeyboardPlayerInput() override = default;

    float GetThrottleValue() override;
    float GetDirection() override;

private:
    Input::KeyboardInputMap inputMap;
};
