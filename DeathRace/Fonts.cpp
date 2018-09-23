#include "Fonts.h"

namespace Fonts {
Font
    defaultFont32px,
    defaultFont14px,
    defaultFont12px,
    defaultFont12pxEdit;

void Load()
{
    defaultFont32px = LoadFont("Content/Fonts/fnt/text/munro-edit-32px.fnt");
    defaultFont14px = LoadFont("Content/Fonts/fnt/text/munro-edit-14px.fnt");
    defaultFont12px = LoadFont("Content/Fonts/fnt/text/munro-12px.fnt");
    defaultFont12pxEdit = LoadFont("Content/Fonts/fnt/text/munro-edit-12px.fnt");
}

void Unload()
{
    UnloadFont(defaultFont32px);
    UnloadFont(defaultFont14px);
    UnloadFont(defaultFont12px);
    UnloadFont(defaultFont12pxEdit);
}
}
