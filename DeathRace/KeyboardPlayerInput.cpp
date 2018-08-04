#include "KeyboardPlayerInput.h"
#include "KeyboardInputMap.h"
#include "raylib.h"
#include <unordered_map>

KeyboardPlayerInput::KeyboardPlayerInput(Input::Keyboard::KeyboardInputMap inputMap)
{
	this->inputMap = inputMap;
}

float KeyboardPlayerInput::GetDirection()
{
	float direction = 0;
	int leftKey = inputMap[Input::InputCommand::Left];
	int rightKey = inputMap[Input::InputCommand::Right];
	
	if (IsKeyDown(leftKey))
	{
		direction -= 1;
	}
	if (IsKeyDown(rightKey))
	{
		direction += 1;
	}

	return direction;
}

float KeyboardPlayerInput::GetThrottleValue()
{
	float throttle = 0;
	int forwardKey = inputMap[Input::InputCommand::Forward];
	int reverseKey = inputMap[Input::InputCommand::Reverse];

	if (IsKeyDown(forwardKey))
	{
		throttle += 1;
	}
	if (IsKeyDown(reverseKey))
	{
		throttle -= 1;
	}

	return throttle;
}

KeyboardPlayerInput::~KeyboardPlayerInput()
{
}
