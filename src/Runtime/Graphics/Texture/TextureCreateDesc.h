#pragma once
#include <Runtime/Graphics/Texture/TextureFormat.h>
#include <Runtime/Graphics/Texture/TextureUsage.h>
#include <Runtime/Graphics/Texture/TextureType.h>

namespace Portakal
{
	/// <summary>
	/// Required information to create texture
	/// </summary>
	struct PORTAKAL_API TextureCreateDesc
	{
		/// <summary>
		/// The type of the texture
		/// </summary>
		TextureType Type;

		/// <summary>
		/// Usage flags for the texture
		/// </summary>
		TextureUsage Usage;

		/// <summary>
		/// The texture format
		/// </summary>
		TextureFormat Format;

		/// <summary>
		/// The width
		/// </summary>
		unsigned int Width;

		/// <summary>
		/// The height
		/// </summary>
		unsigned int Height;

		/// <summary>
		/// The depth
		/// </summary>
		unsigned int Depth;

		/// <summary>
		/// The sample count
		/// </summary>
		unsigned char SampleCount;

		/// <summary>
		/// The mip levels
		/// </summary>
		unsigned char MipLevels;

		/// <summary>
		/// The array levels
		/// </summary>
		unsigned char ArrayLevels;
	};
}