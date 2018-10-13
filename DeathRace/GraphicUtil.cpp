#include "GraphicsUtil.h"
#include <cmath>

void GraphicsUtil::DrawDottedLine(Vector2 startPos, Vector2 endPos, float thickness, Color color)
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

void GraphicsUtil::DrawTexture(Texture2D texture, Vector2 position)
{
    DrawTexture(texture, position, 0, WHITE);
}

void GraphicsUtil::DrawTexture(Texture2D texture, Vector2 position, float rotation, Color tint)
{
    Rectangle sourceRec = { 0.0f, 0.0f, static_cast<float>(texture.width), static_cast<float>(texture.height) };
    Rectangle destRec = { position.x, position.y, static_cast<float>(texture.width), static_cast<float>(texture.height) };
    Vector2 origin = { static_cast<float>(texture.width) / 2, static_cast<float>(texture.height) / 2 };

    DrawTexturePro(texture, sourceRec, destRec, origin, rotation * RAD2DEG, tint);
}

void GraphicsUtil::DrawText(Font font, const char* text, Vector2 pos, float fontSize, float spacing, Color tint)
{
    DrawTextEx(font, text, pos, fontSize, spacing, tint);
}

void GraphicsUtil::DrawText(Font font, std::string text, Vector2 pos, float fontSize, float spacing, Color tint)
{
    GraphicsUtil::DrawText(font, text.c_str(), pos, fontSize, spacing, tint);
}

Vector2 GraphicsUtil::MeasureText(Font font, const char* text, float fontSize, float spacing)
{
    return MeasureTextEx(font, text, fontSize, spacing);
}

Vector2 GraphicsUtil::MeasureText(Font font, std::string text, float fontSize, float spacing)
{
    return GraphicsUtil::MeasureText(font, text.c_str(), fontSize, spacing);
}

Rectangle GraphicsUtil::GetDestinationRectangleForScreen(float screenWidth, float screenHeight, float preferredAspectRatio)
{
    float outputAspectRatio = screenWidth / screenHeight;
    Rectangle destinationRectangle;

    if (outputAspectRatio <= preferredAspectRatio) {
        // letterbox - bars on top and bottom
        float gameHeight = std::round(screenWidth / preferredAspectRatio);
        float barHeight = (screenHeight - gameHeight) / 2;
        destinationRectangle = { 0, barHeight, screenWidth, gameHeight };
    } else {
        // pillarbox - bars on left and right
        float gameWidth = std::round(screenHeight * preferredAspectRatio);
        float barWidth = (screenWidth - gameWidth) / 2;
        destinationRectangle = { barWidth, 0, gameWidth, screenHeight };
    }

    return destinationRectangle;
}
