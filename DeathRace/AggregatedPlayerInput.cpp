#include "AggregatedPlayerInput.h"

AggregatedPlayerInput::AggregatedPlayerInput(std::vector<PlayerInput*> inputs)
{
	this->inputs = inputs;
}

AggregatedPlayerInput::~AggregatedPlayerInput()
{
}

float AggregatedPlayerInput::GetThrottleValue()
{
	float throttle = 0;
	for (auto input : inputs)
	{
		throttle = input->GetThrottleValue();
		if (throttle != 0)
		{
			return throttle;
		}
	}
	return throttle;
}

float AggregatedPlayerInput::GetDirection()
{
	float direction = 0;
	for (auto input : inputs)
	{
		direction = input->GetDirection();
		if (direction != 0)
		{
			return direction;
		}
	}
	return direction;
}
