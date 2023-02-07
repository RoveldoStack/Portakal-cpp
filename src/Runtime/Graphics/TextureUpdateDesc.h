#pragma once
#include <Runtime/Core/Core.h>

namespace Portakal
{
	struct PORTAKAL_API TextureUpdateDesc
	{
		unsigned int MipSlice;
		unsigned int OffsetWidth;
		unsigned int OffsetHeight;
		unsigned int OffsetDepth;
		unsigned int MipLevel;
		unsigned int ArrayLevel;
		const unsigned char* pData;
	};
}