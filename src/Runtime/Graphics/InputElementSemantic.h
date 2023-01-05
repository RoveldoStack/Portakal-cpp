#pragma once
#include <Runtime/Core/Core.h>

namespace Portakal
{
	enum class PORTAKAL_API InputElementSemantic : unsigned char
	{
		Position,
		Normal,
		TextureCoordinate,
		Color
	};
}