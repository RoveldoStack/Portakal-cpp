#pragma once
#include <Runtime/Graphics/TextureFormat.h>

namespace Portakal
{
	struct PORTAKAL_API TextureLoadResult
	{
		unsigned int Width;
		unsigned int Height;
		unsigned int Depth;
		TextureFormat Format;
		const unsigned char* pData;
	};
}