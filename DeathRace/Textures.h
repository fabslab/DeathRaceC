#pragma once

#include "raylib.h"

namespace Textures {
extern Texture
    enemyFront,
    enemyLeft,
    enemyRight,
    marquee,
    player,
    tombstone;
void Load();
void Unload();
}
