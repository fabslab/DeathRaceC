#include "Shaders.h"

namespace Shaders {
Shader
    bloom,
    scanLines;

void Load()
{
    bloom = LoadShader(0, "Content/Shaders/glsl330/bloom.fs");
    scanLines = LoadShader(0, "Content/Shaders/glsl330/scanlines.fs");
}

void Unload()
{
    UnloadShader(bloom);
    UnloadShader(scanLines);
}

void SetDimensions(int width, int height)
{
    int widthInput = GetShaderLocation(bloom, "renderWidth");
    int heightInput = GetShaderLocation(bloom, "renderHeight");
    SetShaderValuei(bloom, widthInput, &width, 1);
    SetShaderValuei(bloom, heightInput, &height, 1);
}
}
