#pragma once
#include <Runtime/Graphics/TextureFormat.h>

namespace Portakal
{
	class PORTAKAL_API TextureUtils
	{
	public:
		TextureUtils() = delete;
		~TextureUtils() = delete;

		FORCEINLINE static unsigned int GetFormatSize(const TextureFormat format);
	};
}