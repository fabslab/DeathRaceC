#pragma once

#include "raylib.h"
#include "raymath.h"
#include <string>

namespace GraphicsUtil {
void DrawDottedLine(Vector2 startPos, Vector2 endPos, float thickness, Color color);
void DrawTexture(Texture2D texture, Vector2 position);
void DrawTexture(Texture2D texture, Vector2 position, float rotation, Color tint);
void DrawText(Font font, const char* text, Vector2 pos, float fontSize, float spacing, Color tint);
void DrawText(Font font, std::string text, Vector2 pos, float fontSize, float spacing, Color tint);
Vector2 MeasureText(Font font, const char* text, float fontSize, float spacing);
Vector2 MeasureText(Font font, std::string text, float fontSize, float spacing);
Rectangle GetDestinationRectangleForScreen(float screenWidth, float screenHeight, float preferredAspectRatio);
}
