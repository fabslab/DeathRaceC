#pragma once

#include "raylib.h"

namespace Shaders {
extern Shader
    bloom,
    scanLines;
void Load();
void Unload();
void SetDimensions(int width, int height);
}
