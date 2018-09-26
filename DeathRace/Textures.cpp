#include "Textures.h"

namespace Textures {
Texture
    enemyFront,
    enemyLeft,
    enemyRight,
    marquee,
    player,
    tombstone;

void Load()
{
    enemyFront = LoadTexture("Content/gremlin-front.png");
    enemyLeft = LoadTexture("Content/gremlin-left.png");
    enemyRight = LoadTexture("Content/gremlin-right.png");
    marquee = LoadTexture("Content/marquee.png");
    player = LoadTexture("Content/car.png");
    tombstone = LoadTexture("Content/cross.png");
}

void Unload()
{
    UnloadTexture(enemyFront);
    UnloadTexture(enemyLeft);
    UnloadTexture(enemyRight);
    UnloadTexture(marquee);
    UnloadTexture(player);
    UnloadTexture(tombstone);
}
}
