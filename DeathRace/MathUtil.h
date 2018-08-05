#pragma once

#include <cmath>

namespace MathUtil {
float Snap(float value, float increment)
{
    return std::round(value / increment) * increment;
}

Vector2 WrapPosition(Vector2 position, Rectangle bounds)
{
    float x = position.x;
    float y = position.y;

    if (position.x < bounds.x) {
        x = bounds.x + bounds.width;
    } else if (position.x > (bounds.x + bounds.width)) {
        x = bounds.x;
    }

    if (position.y < bounds.y) {
        y = bounds.y + bounds.height;
    } else if (position.y > (bounds.y + bounds.height)) {
        y = bounds.y;
    }

    return { x, y };
}
}
