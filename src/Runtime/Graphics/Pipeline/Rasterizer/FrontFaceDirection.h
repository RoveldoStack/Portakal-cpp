#pragma once
#include <Runtime/Core/Core.h>
#include <Runtime/Reflection/Reflection.h>

namespace Portakal
{
	/// <summary>
	/// Available front face directions
	/// </summary>
	PENUM();
	enum class PORTAKAL_API FrontFaceDirection : long long
	{
		Clockwise,
		CounterClockwise
	};

#include "FrontFaceDirection.reflect.h"

}