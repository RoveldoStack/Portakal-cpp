#pragma once
#include <Runtime/Core/Core.h>
#include <Runtime/Containers/String.h>

namespace Portakal
{
	/// <summary>
	/// Required information to create a window
	/// </summary>
	struct PORTAKAL_API WindowCreateDesc
	{
		/// <summary>
		/// Title of the window
		/// </summary>
		String Name;

		/// <summary>
		/// Width of the window
		/// </summary>
		unsigned int Width;

		/// <summary>
		/// Height of the window
		/// </summary>
		unsigned int Height;

		/// <summary>
		/// Position-x of the window
		/// </summary>
		unsigned int PositionX;

		/// <summary>
		/// Position-y of the window
		/// </summary>
		unsigned int PositionY;
	};
}