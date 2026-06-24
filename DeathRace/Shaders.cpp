#include "AssetPath.h"
#include "Shaders.h"

namespace Shaders {
Shader
    bloom,
    scanLines;

void Load()
{
    bloom = LoadShader(0, GetAssetPath("Content/Shaders/glsl330/bloom.fs").c_str());
    scanLines = LoadShader(0, GetAssetPath("Content/Shaders/glsl330/scanlines.fs").c_str());
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
