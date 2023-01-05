#pragma once
#include <Runtime/Containers/String.h>
#include <Runtime/Graphics/TextureLoadResult.h>

namespace Portakal
{
	class PORTAKAL_API TextureLoader
	{
	public:
		TextureLoader() = delete;
		~TextureLoader() = delete;

		FORCEINLINE static bool LoadTextureFromDisk(const String& path, TextureLoadResult& resultOut);
	};
}