#pragma once

#include "raylib.h"

typedef struct EnemyMovementCommand {
    Vector2 position = Vector2{ 0, 0 };
    Vector2 direction = Vector2{ 0, 0 };
} EnemyMovementCommand;
