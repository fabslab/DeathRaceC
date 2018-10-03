#pragma once

#include "InputCommand.h"

class IPlayerInput {
public:
    virtual ~IPlayerInput() = default;
    virtual float GetThrottleValue() = 0;
    virtual float GetDirection() = 0;
    virtual bool WasCommandEntered(Input::InputCommand command) = 0;
};
