#include "KeyboardPlayerInput.h"
#include "KeyboardInputMap.h"
#include "raylib.h"
#include <unordered_map>

KeyboardPlayerInput::KeyboardPlayerInput(Input::KeyboardInputMap inputMap)
    : inputMap(inputMap)
{
}

float KeyboardPlayerInput::GetDirection()
{
    float direction = 0;
    int inputLeft = inputMap[Input::InputCommand::Left];
    int inputRight = inputMap[Input::InputCommand::Right];

    if (IsKeyDown(inputLeft)) {
        direction -= 1;
    }
    if (IsKeyDown(inputRight)) {
        direction += 1;
    }

    return direction;
}

bool KeyboardPlayerInput::WasCommandEntered(Input::InputCommand command)
{
    int input = inputMap[command];
    return IsKeyPressed(input);
}

float KeyboardPlayerInput::GetThrottleValue()
{
    float throttle = 0;
    int inputForward = inputMap[Input::InputCommand::Forward];
    int inputReverse = inputMap[Input::InputCommand::Reverse];

    if (IsKeyDown(inputForward)) {
        throttle += 1;
    }
    if (IsKeyDown(inputReverse)) {
        throttle -= 1;
    }

    return throttle;
}
