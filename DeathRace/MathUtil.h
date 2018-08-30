#pragma once

#include "raylib.h"

bool operator==(const Vector3& v1, const Vector3& v2);

namespace MathUtil {
float Snap(float value, float increment);

Vector2 WrapPosition(Vector2 position, Rectangle bounds);

inline Vector3 Vector2To3(Vector2 v)
{
    return Vector3{ v.x, v.y, 0 };
}
inline Vector2 Vector3To2(Vector3 v)
{
    return Vector2{ v.x, v.y };
}
}

namespace DirectionVectors {
const Vector3 Up = { 0.0f, -1.0f, 0.f };
const Vector3 Right = { 1.0f, 0.0f, 0.f };
const Vector3 Down = { 0.0f, 1.0f, 0.f };
const Vector3 Left = { -1.0f, 0.0f, 0.f };
}
