#include "Textures.h"

namespace Textures {
Texture
    enemyFront,
    enemyLeft,
    enemyRight,
    player;

void Load()
{
    enemyFront = LoadTexture("Content/gremlin-front.png");
    enemyLeft = LoadTexture("Content/gremlin-left.png");
    enemyRight = LoadTexture("Content/gremlin-right.png");
    player = LoadTexture("Content/car.png");
}

void Unload()
{
    UnloadTexture(enemyFront);
    UnloadTexture(enemyLeft);
    UnloadTexture(enemyRight);
    UnloadTexture(player);
}
}
