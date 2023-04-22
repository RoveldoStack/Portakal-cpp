#pragma once
#include <Runtime/Containers/String.h>
#include <Runtime/Graphics/Texture/TextureLoadResult.h>

namespace Portakal
{
	/// <summary>
	/// Utility class for loading textures
	/// </summary>
	class PORTAKAL_API TextureLoader
	{
	public:
		TextureLoader() = delete;
		~TextureLoader() = delete;

		/// <summary>
		/// Loads the texture via a path
		/// </summary>
		/// <param name="path"></param>
		/// <param name="resultOut"></param>
		/// <returns></returns>
		FORCEINLINE static bool LoadTextureFromDisk(const String& path, TextureLoadResult& resultOut);
	};
}