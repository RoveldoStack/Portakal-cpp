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
		String Name;
		unsigned int Width;
		unsigned int Height;
		unsigned int PositionX;
		unsigned int PositionY;
	};
}