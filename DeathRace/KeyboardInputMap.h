#pragma once

#include "InputCommand.h"
#include "raylib.h"
#include <unordered_map>

namespace Input {
using KeyboardInputMap = std::unordered_map<InputCommand, int>;

const KeyboardInputMap PLAYER_LEFT = {
    { InputCommand::Forward, KEY_W },
    { InputCommand::Right, KEY_D },
    { InputCommand::Reverse, KEY_S },
    { InputCommand::Left, KEY_A },
};

const KeyboardInputMap PLAYER_RIGHT = {
    { InputCommand::Forward, KEY_UP },
    { InputCommand::Right, KEY_RIGHT },
    { InputCommand::Reverse, KEY_DOWN },
    { InputCommand::Left, KEY_LEFT },
};

const KeyboardInputMap UI_NAVIGATION = {
    { InputCommand::Up, KEY_UP },
    { InputCommand::Right, KEY_RIGHT },
    { InputCommand::Down, KEY_DOWN },
    { InputCommand::Left, KEY_LEFT },
    { InputCommand::Enter, KEY_ENTER },
    { InputCommand::Back, KEY_ESCAPE },
    { InputCommand::Pause, KEY_ESCAPE },
};
}
