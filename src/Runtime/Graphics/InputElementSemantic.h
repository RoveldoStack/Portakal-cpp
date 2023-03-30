#pragma once
#include <Runtime/Core/Core.h>

namespace Portakal
{
	/// <summary>
	/// Available input semantic types
	/// </summary>
	enum class PORTAKAL_API InputElementSemantic : unsigned char
	{
		Position,
		Normal,
		TextureCoordinate,
		Color,
		COUNT
	};
}