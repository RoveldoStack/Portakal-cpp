#pragma once
#include <Runtime/Core/Core.h>

namespace Portakal
{
	/// <summary>
	/// Required information to update a graphics bufer
	/// </summary>
	struct PORTAKAL_API GraphicsBufferUpdateDesc
	{
		/// <summary>
		/// The data offset
		/// </summary>
		unsigned long long Offset;

		/// <summary>
		/// The data region size
		/// </summary>
		unsigned long long Size;

		/// <summary>
		/// The data
		/// </summary>
		const Byte* pData;
	};
}