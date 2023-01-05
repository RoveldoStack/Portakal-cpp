#pragma once
#include <Runtime/Graphics/TextureFormat.h>
#include <Runtime/Graphics/TextureUsage.h>
#include <Runtime/Graphics/TextureType.h>

namespace Portakal
{
	struct PORTAKAL_API TextureCreateDesc
	{
		TextureType Type;
		TextureUsage Usage;
		TextureFormat Format;
		unsigned int Width;
		unsigned int Height;
		unsigned int Depth;
		unsigned char SampleCount;
		unsigned char MipLevels;
		unsigned char ArrayLevels;
	};
}