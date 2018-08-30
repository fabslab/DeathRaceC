#pragma once

#include "raylib.h"
#include "raymath.h"

namespace GraphicUtil {
void DrawDottedLine(Vector2 startPos, Vector2 endPos, float thickness, Color color);
void DrawTexture(Texture2D texture, Vector2 position);
void DrawTexture(Texture2D texture, Vector2 position, float rotation, Color tint);
Rectangle GetDestinationRectangleForScreen(float screenWidth, float screenHeight, float preferredAspectRatio);
}
