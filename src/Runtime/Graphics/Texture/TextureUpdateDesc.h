#pragma once
#include <Runtime/Core/Core.h>

namespace Portakal
{
	/// <summary>
	/// Required information to update a texture
	/// </summary>
	struct PORTAKAL_API TextureUpdateDesc
	{
		/// <summary>
		/// Mip slice index
		/// </summary>
		unsigned int MipSlice;

		/// <summary>
		/// Width offset
		/// </summary>
		unsigned int OffsetWidth;

		/// <summary>
		/// Height offset
		/// </summary>
		unsigned int OffsetHeight;

		/// <summary>
		/// Depth offset
		/// </summary>
		unsigned int OffsetDepth;

		/// <summary>
		/// Array level index
		/// </summary>
		unsigned int ArrayLevel;

		/// <summary>
		/// The target data
		/// </summary>
		const unsigned char* pData;
	};
}