#include "ControllerPlayerInput.h"

ControllerPlayerInput::ControllerPlayerInput(Input::ControllerInputMap inputMap, PlayerIndex playerIndex)
    : inputMap(inputMap)
    , playerIndex(playerIndex)
{
}

float ControllerPlayerInput::GetDirection()
{
    float direction = 0;
    int gamepadIndex = static_cast<int>(playerIndex);

    if (IsGamepadAvailable(gamepadIndex)) {
        int inputLeft = inputMap[Input::InputCommand::Left];
        int inputRight = inputMap[Input::InputCommand::Right];

        if (IsGamepadButtonDown(gamepadIndex, inputLeft)) {
            direction -= 1;
        }
        if (IsGamepadButtonDown(gamepadIndex, inputRight)) {
            direction += 1;
        }
    }

    return direction;
}

bool ControllerPlayerInput::WasCommandEntered(Input::InputCommand command)
{
    int gamepadIndex = static_cast<int>(playerIndex);
    int input = inputMap[command];
    return IsGamepadButtonPressed(gamepadIndex, input);
}

float ControllerPlayerInput::GetThrottleValue()
{
    float throttle = 0;
    int gamepadIndex = static_cast<int>(playerIndex);

    if (IsGamepadAvailable(gamepadIndex)) {
        int inputForward = inputMap[Input::InputCommand::Forward];
        int inputReverse = inputMap[Input::InputCommand::Reverse];

        if (IsGamepadButtonDown(gamepadIndex, inputForward)) {
            throttle += 1;
        }
        if (IsGamepadButtonDown(gamepadIndex, inputReverse)) {
            throttle -= 1;
        }
    }

    return throttle;
}
