#pragma once
#include <Runtime/Core/Core.h>

namespace Portakal
{
	struct PORTAKAL_API ViewportDesc
	{
		unsigned int X;
		unsigned int Y;
		unsigned int Width;
		unsigned int Height;
		float MinDepth;
		float MaxDepth;
	};
}