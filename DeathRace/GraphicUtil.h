#pragma once

#include "raylib.h"
#include "raymath.h"

namespace GraphicUtil {
void DrawDottedLine(Vector2 startPos, Vector2 endPos, float thickness, Color color);
void DrawTexture(Texture2D texture, Vector2 position);
void DrawTexture(Texture2D texture, Vector2 position, float rotation, Color tint);

class AnimatedTexture {
public:
    AnimatedTexture(const char* fileName, int frameCount, float frameDurationMs);
    ~AnimatedTexture();
    void Update();
    void Draw(Vector2 position);

private:
    int frameCount, frameWidth, currentFrameIndex;
    float remainingFrameTime, frameDurationMs;
    Texture2D texture;
};
}
