#pragma once

#include "KeyboardInputMap.h"
#include "PlayerInput.h"
#include <unordered_map>

class KeyboardPlayerInput : public PlayerInput
{
public:
	KeyboardPlayerInput(Input::Keyboard::KeyboardInputMap inputMap);
	~KeyboardPlayerInput() override;

	float GetThrottleValue() override;
	float GetDirection() override;
private:
	Input::Keyboard::KeyboardInputMap inputMap;
};

