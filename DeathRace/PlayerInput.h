#pragma once

class PlayerInput {
public:
    virtual ~PlayerInput() = default;
    virtual float GetThrottleValue() = 0;
    virtual float GetDirection() = 0;
};
