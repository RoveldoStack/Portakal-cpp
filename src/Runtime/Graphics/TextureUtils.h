#pragma once
#include <Runtime/Graphics/TextureFormat.h>

namespace Portakal
{
	/// <summary>
	/// Utility class for texture operations
	/// </summary>
	class PORTAKAL_API TextureUtils
	{
	public:
		TextureUtils() = delete;
		~TextureUtils() = delete;

		/// <summary>
		/// Returns the texture format sizes
		/// </summary>
		/// <param name="format"></param>
		/// <returns></returns>
		FORCEINLINE static unsigned int GetFormatSize(const TextureFormat format);
	};
}