#include "MathUtil.h"
#include <cmath>

bool operator==(const Vector3& v1, const Vector3& v2)
{
    return (v1.x == v2.x && v1.y == v2.y && v1.z == v2.z);
}

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
