#include "AssetPath.h"
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
    enemyFront = LoadTexture(GetAssetPath("Content/gremlin-front.png").c_str());
    enemyLeft = LoadTexture(GetAssetPath("Content/gremlin-left.png").c_str());
    enemyRight = LoadTexture(GetAssetPath("Content/gremlin-right.png").c_str());
    marquee = LoadTexture(GetAssetPath("Content/marquee.png").c_str());
    player = LoadTexture(GetAssetPath("Content/car.png").c_str());
    tombstone = LoadTexture(GetAssetPath("Content/cross.png").c_str());
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
