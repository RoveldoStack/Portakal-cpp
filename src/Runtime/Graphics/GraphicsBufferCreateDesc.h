#pragma once
#include <Runtime/Graphics/GraphicsBufferType.h>

namespace Portakal
{
	struct PORTAKAL_API GraphicsBufferCreateDesc
	{
		GraphicsBufferType Type;
		unsigned long long SubItemSize;
		unsigned long long SubItemCount;
	};
}