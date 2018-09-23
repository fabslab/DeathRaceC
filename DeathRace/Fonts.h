#pragma once

#include "raylib.h"

namespace Fonts {
extern Font
    defaultFont32px,
    defaultFont14px,
    defaultFont12px,
    defaultFont12pxEdit;
void Load();
void Unload();
}
