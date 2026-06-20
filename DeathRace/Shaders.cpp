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
    SetShaderValue(bloom, widthInput, &width, SHADER_UNIFORM_INT);
    SetShaderValue(bloom, heightInput, &height, SHADER_UNIFORM_INT);
}
}
