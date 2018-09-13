#include "Fonts.h"

namespace Fonts {
Font
    defaultFont32px;

void Load()
{
    defaultFont32px = LoadFont("Content/Fonts/fnt/text/munro-edit-32px.fnt");
}

void Unload()
{
    UnloadFont(defaultFont32px);
}
}
