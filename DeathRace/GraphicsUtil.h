#pragma once

#include "raylib.h"
#include "raymath.h"
#include <string>

namespace GraphicsUtil {
void DrawDottedLine(Vector2 startPos, Vector2 endPos, float thickness, Color color);
void DrawTexture(Texture2D texture, Vector2 position);
void DrawTexture(Texture2D texture, Vector2 position, float rotation, Color tint);
void DrawText(const char* text, Vector2 pos, float fontSize, float spacing);
void DrawText(std::string text, Vector2 pos, float fontSize, float spacing);
Vector2 MeasureText(const char* text, float fontSize, float spacing);
Vector2 MeasureText(std::string text, float fontSize, float spacing);
Rectangle GetDestinationRectangleForScreen(float screenWidth, float screenHeight, float preferredAspectRatio);
}
