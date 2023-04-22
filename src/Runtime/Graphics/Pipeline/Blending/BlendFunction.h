#pragma once
#include <Runtime/Core/Core.h>

namespace Portakal
{
	/// <summary>
	/// Represents the available blending functions
	/// </summary>
	enum class PORTAKAL_API BlendFunction
	{
		Add,
		Subtract,
		ReverseSubtract,
		Minimum,
		Maximum
	};
}