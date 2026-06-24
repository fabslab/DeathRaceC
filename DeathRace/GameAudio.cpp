#include "AssetPath.h"
#include "Textures.h"

namespace GameAudio {
Sound
    collision,
    scream;

void Load()
{
    collision = LoadSound(GetAssetPath("Content/Audio/collision.ogg").c_str());
    scream = LoadSound(GetAssetPath("Content/Audio/scream.ogg").c_str());
}

void Unload()
{
    UnloadSound(collision);
    UnloadSound(scream);
}
}
