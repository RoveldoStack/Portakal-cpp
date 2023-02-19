#pragma once
#include <Runtime/Core/Core.h>

namespace Portakal
{
	/// <summary>
	/// Required information to specify a viewport
	/// </summary>
	struct PORTAKAL_API ViewportDesc
	{
		/// <summary>
		/// Offset-X
		/// </summary>
		unsigned int X;

		/// <summary>
		/// Offset-Y
		/// </summary>
		unsigned int Y;

		/// <summary>
		/// Width
		/// </summary>
		unsigned int Width;

		/// <summary>
		/// Height
		/// </summary>
		unsigned int Height;

		/// <summary>
		/// Min depth value
		/// </summary>
		float MinDepth;

		/// <summary>
		/// Max depth value
		/// </summary>
		float MaxDepth;
	};
}