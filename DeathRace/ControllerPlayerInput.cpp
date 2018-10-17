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
        int directionAxis = inputMap[Input::InputCommand::DirectionXAxis];

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
        int inputForwardButton = inputMap[Input::InputCommand::ForwardButton];
        int inputReverseButton = inputMap[Input::InputCommand::ReverseButton];

        float forwardAxis = GetGamepadAxisMovement(gamepadIndex, inputForward);
        bool fowardButtonDown = IsGamepadButtonDown(gamepadIndex, inputForwardButton);
        if (forwardAxis >= .1f || fowardButtonDown) {
            throttle += 1;
        }

        float reverseAxis = GetGamepadAxisMovement(gamepadIndex, inputReverse);
        bool reverseButtonDown = IsGamepadButtonDown(gamepadIndex, inputReverseButton);
        if (reverseAxis >= .1f || reverseButtonDown) {
            throttle -= 1;
        }
    }

    return throttle;
}

Input::ControllerInputMap ControllerPlayerInput::GetInputMap(int gamepadIndex)
{
    if (IsGamepadName(gamepadIndex, "Wireless Controller")) {
        return Input::PS4_GAMEPAD;
    }
    if (IsGamepadName(gamepadIndex, "Xbox Controller") || IsGamepadName(gamepadIndex, "Wireless Xbox Controller")) {
        return Input::XBO_GAMEPAD;
    }
    if (IsGamepadName(gamepadIndex, "Xbox Wireless Controller")) {
        return Input::XBO_WIRELESS_GAMEPAD;
    }
    return Input::PS4_GAMEPAD;
}
