#pragma once

class IPlayerInput {
public:
    virtual ~IPlayerInput() = default;
    virtual float GetThrottleValue() = 0;
    virtual float GetDirection() = 0;
};
