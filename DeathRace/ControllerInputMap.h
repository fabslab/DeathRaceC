#pragma once

#include "InputCommand.h"
#include "raylib.h"
#include <unordered_map>

namespace Input {
using ControllerInputMap = std::unordered_map<InputCommand, int>;

const ControllerInputMap PS4_GAMEPAD = {
    { InputCommand::Enter, 1 },
    { InputCommand::Back, 2 },
    { InputCommand::Reverse, 6 },
    { InputCommand::Forward, 7 },
    { InputCommand::Pause, 9 },
    { InputCommand::Up, 14 },
    { InputCommand::Right, 15 },
    { InputCommand::Down, 16 },
    { InputCommand::Left, 17 },
};
}
