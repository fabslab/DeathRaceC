#pragma once

class PlayerInput
{
public:
	virtual float GetThrottleValue() = 0;
	virtual float GetDirection() = 0;
};
