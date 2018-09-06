#include "Textures.h"

namespace Textures {
Texture
    enemyFront,
    enemyLeft,
    enemyRight,
    player,
    tombstone;

void Load()
{
    enemyFront = LoadTexture("Content/gremlin-front.png");
    enemyLeft = LoadTexture("Content/gremlin-left.png");
    enemyRight = LoadTexture("Content/gremlin-right.png");
    player = LoadTexture("Content/car.png");
    tombstone = LoadTexture("Content/cross.png");
}

void Unload()
{
    UnloadTexture(enemyFront);
    UnloadTexture(enemyLeft);
    UnloadTexture(enemyRight);
    UnloadTexture(player);
    UnloadTexture(tombstone);
}
}
