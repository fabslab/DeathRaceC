#pragma once

#include "ControllerInputMap.h"
#include "IPlayerInput.h"
#include "PlayerIndex.h"

class ControllerPlayerInput : public IPlayerInput {
public:
    ControllerPlayerInput(Input::ControllerInputMap inputMap, PlayerIndex playerIndex);
    ~ControllerPlayerInput() override = default;
    float GetThrottleValue() override;
    float GetDirection() override;
    bool WasCommandEntered(Input::InputCommand command) override;

private:
    Input::ControllerInputMap inputMap;
    PlayerIndex playerIndex;
};
