#pragma once
#include <Runtime/Core/Core.h>

namespace Portakal
{
	/// <summary>
	/// Represents a rect for scissors
	/// </summary>
	struct PORTAKAL_API ScissorDesc
	{
		/// <summary>
		/// Offset x
		/// </summary>
		unsigned int X;

		/// <summary>
		/// Offset y
		/// </summary>
		unsigned int Y;

		/// <summary>
		/// The width of the rect
		/// </summary>
		unsigned int Width;

		/// <summary>
		/// The height of the rect
		/// </summary>
		unsigned int Height;
	};
}