#include "ControllerPlayerInput.h"

ControllerPlayerInput::ControllerPlayerInput(PlayerIndex playerIndex)
    : playerIndex(playerIndex)
{
}

float ControllerPlayerInput::GetDirection()
{
    float direction = 0;
    int gamepadIndex = static_cast<int>(playerIndex);

    if (IsGamepadAvailable(gamepadIndex)) {
        auto inputMap = GetInputMap(gamepadIndex);
        int inputLeft = inputMap[Input::InputCommand::Left];
        int inputRight = inputMap[Input::InputCommand::Right];
        int directionAxis = inputMap[Input::InputCommand::DirectionAxis];

        if (IsGamepadButtonDown(gamepadIndex, inputLeft) || GetGamepadAxisMovement(gamepadIndex, directionAxis) < -0.25f) {
            direction -= 1;
        }
        if (IsGamepadButtonDown(gamepadIndex, inputRight) || GetGamepadAxisMovement(gamepadIndex, directionAxis) > 0.25f) {
            direction += 1;
        }
    }

    return direction;
}

bool ControllerPlayerInput::WasCommandEntered(Input::InputCommand command)
{
    bool entered = false;
    int gamepadIndex = static_cast<int>(playerIndex);
    if (IsGamepadAvailable(gamepadIndex)) {
        auto inputMap = GetInputMap(gamepadIndex);
        int input = inputMap[command];
        entered = IsGamepadButtonPressed(gamepadIndex, input);
    }
    return entered;
}

float ControllerPlayerInput::GetThrottleValue()
{
    float throttle = 0;
    int gamepadIndex = static_cast<int>(playerIndex);

    if (IsGamepadAvailable(gamepadIndex)) {
        auto inputMap = GetInputMap(gamepadIndex);
        int inputForward = inputMap[Input::InputCommand::ForwardAxis];
        int inputReverse = inputMap[Input::InputCommand::ReverseAxis];

        if (GetGamepadAxisMovement(gamepadIndex, inputForward) >= 0.f) {
            throttle += 1;
        }
        if (GetGamepadAxisMovement(gamepadIndex, inputReverse) >= 0.f) {
            throttle -= 1;
        }
    }

    return throttle;
}

Input::ControllerInputMap ControllerPlayerInput::GetInputMap(int gamepadIndex)
{
    if (IsGamepadName(gamepadIndex, "Wireless Controller")) {
        return Input::PS4_GAMEPAD;
    } else {
        return Input::XBO_GAMEPAD;
    }
}
