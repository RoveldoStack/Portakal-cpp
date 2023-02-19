#pragma once
#include <Runtime/Graphics/TextureFormat.h>

namespace Portakal
{
	/// <summary>
	/// Utility class for texture loader format conversions
	/// </summary>
	class PORTAKAL_API TextureLoaderUtils
	{
	public:
		TextureLoaderUtils() = delete;
		~TextureLoaderUtils() = delete;

		/// <summary>
		/// Returns the texture format according to the given channels
		/// </summary>
		/// <param name="channels"></param>
		/// <returns></returns>
		FORCEINLINE static TextureFormat GetTextureFormat(const unsigned int channels);
	};
}