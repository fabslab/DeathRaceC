#pragma once

#include "InputCommand.h"
#include "raylib.h"
#include <unordered_map>

namespace Input {
using KeyboardInputMap = std::unordered_map<InputCommand, int>;

const KeyboardInputMap PLAYER_LEFT = {
    { InputCommand::ForwardAxis, KEY_W },
    { InputCommand::Right, KEY_D },
    { InputCommand::ReverseAxis, KEY_S },
    { InputCommand::Left, KEY_A },
};

const KeyboardInputMap PLAYER_RIGHT = {
    { InputCommand::ForwardAxis, KEY_UP },
    { InputCommand::Right, KEY_RIGHT },
    { InputCommand::ReverseAxis, KEY_DOWN },
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
