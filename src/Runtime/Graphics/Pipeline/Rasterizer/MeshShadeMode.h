#pragma once
#include <Runtime/Core/Core.h>
#include <Runtime/Reflection/Reflection.h>
namespace Portakal
{
	/// <summary>
	/// Available mesh shading modes
	/// </summary>
	ENUM();
	enum class PORTAKAL_API MeshShadeMode : long long
	{
		Solid,
		Wireframe
	};

#include "MeshShadeMode.reflect.h"
}