#pragma once
#include <Runtime/Graphics/Buffer/GraphicsBufferType.h>

namespace Portakal
{
	/// <summary>
	/// Required information to create graphics buffer
	/// </summary>
	struct PORTAKAL_API GraphicsBufferCreateDesc
	{
		/// <summary>
		/// The type of the buffer
		/// </summary>
		GraphicsBufferType Type;

		/// <summary>
		/// Single sub item size in bytes
		/// </summary>
		unsigned long long SubItemSize;

		/// <summary>
		/// Sub item count
		/// </summary>
		unsigned long long SubItemCount;
	};
}