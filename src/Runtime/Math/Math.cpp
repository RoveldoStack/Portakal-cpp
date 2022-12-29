
#include "Math.h"
#include <cmath>

namespace Portakal
{
	float Math::Sqrt(const float value)
	{
		return sqrt(value);
	}
	float Math::Cos(const float rad)
	{
		return cos(rad);
	}
	float Math::Sin(const float rad)
	{
		return sin(rad);
	}
	float Math::Tan(const float rad)
	{
		return tan(rad);
	}
	float Math::Abs(const float value)
	{
		return value < 0 ? -value : value;
	}
}