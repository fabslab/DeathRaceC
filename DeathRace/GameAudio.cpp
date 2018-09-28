#include "Textures.h"

namespace GameAudio {
Sound
    collision,
    scream;

void Load()
{
    collision = LoadSound("Content/Audio/collision.ogg");
    scream = LoadSound("Content/Audio/scream.ogg");
}

void Unload()
{
    UnloadSound(collision);
    UnloadSound(scream);
}
}
