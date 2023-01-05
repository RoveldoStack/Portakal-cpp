#pragma once
#include <Runtime/Core/Core.h>

namespace Portakal
{
	struct PORTAKAL_API GraphicsBufferUpdateDesc
	{
		unsigned long long Offset;
		unsigned long long Size;
		const unsigned char* pData;
	};
}