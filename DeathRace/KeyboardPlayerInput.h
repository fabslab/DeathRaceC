#pragma once

#include "KeyboardInputMap.h"
#include "PlayerInput.h"
#include <unordered_map>

class KeyboardPlayerInput : public PlayerInput
{
public:
	KeyboardPlayerInput(Input::Keyboard::KeyboardInputMap inputMap);
	~KeyboardPlayerInput();

	virtual float GetThrottleValue() override;
	virtual float GetDirection() override;
private:
	Input::Keyboard::KeyboardInputMap inputMap;
};

