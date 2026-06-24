#include "AssetPath.h"
#include "Fonts.h"

namespace Fonts {
Font
    defaultFont32px,
    defaultFont14px,
    defaultFont12px,
    defaultFont12pxEdit;

void Load()
{
    defaultFont32px = LoadFont(GetAssetPath("Content/Fonts/fnt/text/munro-edit-32px.fnt").c_str());
    defaultFont14px = LoadFont(GetAssetPath("Content/Fonts/fnt/text/munro-edit-14px.fnt").c_str());
    defaultFont12px = LoadFont(GetAssetPath("Content/Fonts/fnt/text/munro-12px.fnt").c_str());
    defaultFont12pxEdit = LoadFont(GetAssetPath("Content/Fonts/fnt/text/munro-edit-12px.fnt").c_str());
}

void Unload()
{
    UnloadFont(defaultFont32px);
    UnloadFont(defaultFont14px);
    UnloadFont(defaultFont12px);
    UnloadFont(defaultFont12pxEdit);
}
}
