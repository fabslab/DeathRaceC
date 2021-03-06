#pragma once

#include "ECS.h"
#include "PlayerIndex.h"
#include "raylib.h"

namespace Entities {
void CreateEnemy(ECS::World* world, Vector2 position);
void CreatePlayer(ECS::World* world, PlayerIndex playerIndex, Vector2 position, Color color);
void CreateTombstone(ECS::World* world, Vector2 position);
}
