#include "GraphicUtil.h"

void GraphicUtil::DrawDottedLine(Vector2 startPos, Vector2 endPos, float thickness, Color color)
{
    Vector2 dashStart = Vector2(startPos);
    Vector2 dash = Vector2Scale(Vector2Normalize(Vector2Subtract(endPos, startPos)), thickness);
    Vector2 dashEnd = Vector2Add(dashStart, dash);

    while (dashEnd.x <= endPos.x && dashEnd.y <= endPos.y) {
        DrawLineEx(dashStart, dashEnd, thickness, color);
        dashStart = Vector2Add(dashEnd, Vector2Scale(dash, 2));
        dashEnd = Vector2Add(dashStart, dash);
    }
}

void GraphicUtil::DrawTexture(Texture2D texture, Vector2 position)
{
    DrawTexture(texture, position, 0, WHITE);
}

void GraphicUtil::DrawTexture(Texture2D texture, Vector2 position, float rotation, Color tint)
{
    Rectangle sourceRec = { 0.0f, 0.0f, static_cast<float>(texture.width), static_cast<float>(texture.height) };
    Rectangle destRec = { position.x, position.y, static_cast<float>(texture.width), static_cast<float>(texture.height) };
    Vector2 origin = { static_cast<float>(texture.width) / 2, static_cast<float>(texture.height) / 2 };

    DrawTexturePro(texture, sourceRec, destRec, origin, rotation * RAD2DEG, tint);
}

GraphicUtil::AnimatedTexture::AnimatedTexture(const char* fileName, int frameCount, float frameDurationMs)
    : frameCount(frameCount)
    , frameDurationMs(frameDurationMs)
{
    texture = LoadTexture(fileName);
    frameWidth = texture.width / frameCount;
    Reset();
}

GraphicUtil::AnimatedTexture::~AnimatedTexture()
{
    UnloadTexture(texture);
}

void GraphicUtil::AnimatedTexture::Update(float frameTimeMs)
{
    remainingFrameTime -= frameTimeMs;
    if (remainingFrameTime <= 0) {
        ++currentFrameIndex %= frameCount;
        remainingFrameTime = frameDurationMs;
    }
}

void GraphicUtil::AnimatedTexture::Draw(Vector2 position)
{
    Rectangle currentFrame = Rectangle{ static_cast<float>(frameWidth * currentFrameIndex), 0.0f, static_cast<float>(frameWidth), static_cast<float>(texture.height) };
    Rectangle destRec = { position.x, position.y, static_cast<float>(frameWidth), static_cast<float>(texture.height) };
    Vector2 origin = { static_cast<float>(frameWidth) / 2, static_cast<float>(texture.height) / 2 };

    DrawTexturePro(texture, currentFrame, destRec, origin, 0, WHITE);
}

void GraphicUtil::AnimatedTexture::Reset()
{
    currentFrameIndex = 0;
    remainingFrameTime = frameDurationMs;
}
