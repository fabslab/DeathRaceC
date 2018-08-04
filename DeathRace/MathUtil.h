#pragma once

#include <cmath>

namespace MathUtil
{
	float Snap(float value, float increment)
	{
		return std::round(value / increment) * increment;
	}
}