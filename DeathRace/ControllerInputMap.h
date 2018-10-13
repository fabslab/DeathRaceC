#pragma once

#include "InputCommand.h"
#include "raylib.h"
#include <unordered_map>

namespace Input {
using ControllerInputMap = std::unordered_map<InputCommand, int>;

const ControllerInputMap PS4_GAMEPAD = {
    { InputCommand::Enter, 1 },
    { InputCommand::Back, 2 },
    { InputCommand::Reverse, 3 },
    { InputCommand::Forward, 4 },
    { InputCommand::Pause, 9 },
    { InputCommand::Up, 14 },
    { InputCommand::Right, 15 },
    { InputCommand::Down, 16 },
    { InputCommand::Left, 17 },
};

const ControllerInputMap XBO_GAMEPAD = {
    { InputCommand::Enter, 0 },
    { InputCommand::Back, 1 },
    { InputCommand::Reverse, 4 },
    { InputCommand::Forward, 5 },
    { InputCommand::Pause, 7 },
    { InputCommand::Up, 10 },
    { InputCommand::Right, 11 },
    { InputCommand::Down, 12 },
    { InputCommand::Left, 13 },
};
}
