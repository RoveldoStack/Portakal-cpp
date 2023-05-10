#pragma once
#include <Runtime/Core/Core.h>

namespace Portakal
{
	/// <summary>
	/// Represents a rect for scissors
	/// </summary>
	struct PORTAKAL_API ScissorDesc
	{
		float Top;
		float Bottom;
		float Left;
		float Right;
	};
}