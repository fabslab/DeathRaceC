#pragma once

#include "raylib.h"

bool operator==(const Vector2& v1, const Vector2& v2);

namespace MathUtil {
float Snap(float value, float increment);
Vector2 WrapPosition(Vector2 position, Rectangle bounds);
}

namespace DirectionVectors {
const Vector2 Up = { 0.0f, -1.0f };
const Vector2 Right = { 1.0f, 0.0f };
const Vector2 Down = { 0.0f, 1.0f };
const Vector2 Left = { -1.0f, 0.0f };
}
