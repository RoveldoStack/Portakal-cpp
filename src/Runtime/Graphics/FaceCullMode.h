#pragma once
#include <Runtime/Core/Core.h>

namespace Portakal
{
	/// <summary>
	/// Available face culling modes
	/// </summary>
	enum class PORTAKAL_API FaceCullMode : unsigned char
	{
		Back,
		Front,
		None
	};
}