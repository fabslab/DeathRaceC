#pragma once

#include "PlayerInput.h"
#include <vector>

class AggregatedPlayerInput : public PlayerInput
{
public:
	AggregatedPlayerInput(std::vector<PlayerInput*> inputs);
	~AggregatedPlayerInput();

	virtual float GetThrottleValue() override;
	virtual float GetDirection() override;

private:
	std::vector<PlayerInput*> inputs;
};
