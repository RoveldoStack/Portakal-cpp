#pragma once
#include <Runtime/Graphics/TextureFormat.h>

namespace Portakal
{
	/// <summary>
	/// Output data for the texture loading
	/// </summary>
	struct PORTAKAL_API TextureLoadResult
	{
		/// <summary>
		/// The width of the texture
		/// </summary>
		unsigned int Width;

		/// <summary>
		/// The height of the texture
		/// </summary>
		unsigned int Height;

		/// <summary>
		/// The depth of the texture
		/// </summary>
		unsigned int Depth;

		/// <summary>
		/// The format of texture
		/// </summary>
		TextureFormat Format;

		/// <summary>
		/// The uncompressed data
		/// </summary>
		const unsigned char* pData;
	};
}