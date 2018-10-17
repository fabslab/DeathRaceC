#pragma once

#include "InputCommand.h"
#include "raylib.h"
#include <unordered_map>

namespace Input {
using ControllerInputMap = std::unordered_map<InputCommand, int>;

const ControllerInputMap PS4_GAMEPAD = {
    { InputCommand::Enter, 1 },
    { InputCommand::Back, 2 },
    { InputCommand::ReverseAxis, 3 },
    { InputCommand::ForwardAxis, 4 },
    { InputCommand::ReverseButton, 4 },
    { InputCommand::ForwardButton, 5 },
    { InputCommand::Pause, 9 },
    { InputCommand::Up, 14 },
    { InputCommand::Right, 15 },
    { InputCommand::Down, 16 },
    { InputCommand::Left, 17 },
    { InputCommand::DirectionXAxis, 0 },
    { InputCommand::DirectionYAxis, 1 }
};

const ControllerInputMap XBO_GAMEPAD = {
    { InputCommand::Enter, 0 },
    { InputCommand::Back, 1 },
    { InputCommand::ReverseAxis, 4 },
    { InputCommand::ForwardAxis, 5 },
    { InputCommand::ReverseButton, 4 },
    { InputCommand::ForwardButton, 5 },
    { InputCommand::Pause, 7 },
    { InputCommand::Up, 10 },
    { InputCommand::Right, 11 },
    { InputCommand::Down, 12 },
    { InputCommand::Left, 13 },
    { InputCommand::DirectionXAxis, 0 },
    { InputCommand::DirectionYAxis, 1 }
};

const ControllerInputMap XBO_WIRELESS_GAMEPAD = {
    { InputCommand::Enter, 0 },
    { InputCommand::Back, 1 },
    { InputCommand::ReverseAxis, -1 },
    { InputCommand::ForwardAxis, -1 },
    { InputCommand::ReverseButton, 6 },
    { InputCommand::ForwardButton, 7 },
    { InputCommand::Pause, 11 },
    { InputCommand::Up, 15 },
    { InputCommand::Right, 16 },
    { InputCommand::Down, 17 },
    { InputCommand::Left, 18 },
    { InputCommand::DirectionXAxis, 0 },
    { InputCommand::DirectionYAxis, 1 }
};
}
