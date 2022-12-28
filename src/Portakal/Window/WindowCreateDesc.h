#pragma once
#include <Portakal/Core/Core.h>
#include <string>

namespace Portakal
{
	/// <summary>
	/// Required information to create a window
	/// </summary>
	struct PORTAKAL_API WindowCreateDesc
	{
		std::string Name;
		unsigned int Width;
		unsigned int Height;
		unsigned int PositionX;
		unsigned int PositionY;
	};
}