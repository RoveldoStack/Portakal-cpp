#pragma once
#include <Runtime/Core/Core.h>
#include <Runtime/Reflection/Reflection.h>
namespace Portakal
{
	/// <summary>
	/// Available face culling modes
	/// </summary>
	ENUM();
	enum class PORTAKAL_API FaceCullMode : unsigned char
	{
		Back,
		Front,
		None
	};

#include "FaceCullMode.reflect.h"
}