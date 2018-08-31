#pragma once

#include "raylib.h"

typedef struct PlayerMovementCommand {
    Vector2 position = Vector2{ 0, 0 };
    float rotation = 0.f;
} PlayerMovementCommand;
