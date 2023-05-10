#pragma once
#include <Runtime/Core/Core.h>

namespace Portakal
{
	enum class PORTAKAL_API BlendingColorWriteFlags : unsigned int
	{
		None = 0x0,
		Red = 0x1,
		Green = 0x2,
		Blue = 0x4,
		Alpha = 0x8,
		All = 0xF
	};

	GENERATE_FLAG_OPERATORS(BlendingColorWriteFlags,unsigned int);
}