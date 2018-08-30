#pragma once

#include "raylib.h"

typedef struct MovementCommand {
    Vector2 position = { 0, 0 };
    float rotation = 0.f;
} MovementCommand;
