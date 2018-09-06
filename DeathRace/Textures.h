#pragma once

#include "raylib.h"

namespace Textures {
extern Texture
    enemyFront,
    enemyLeft,
    enemyRight,
    player,
    tombstone;
void Load();
void Unload();
}
