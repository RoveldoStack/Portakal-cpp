#pragma once
#include <Runtime/Reflection/Reflection.h>
#include <Runtime/Containers/Guid.h>

namespace Portakal
{
	/// <summary>
	/// Represents a single resource entry inside the scene
	/// </summary>
	PSTRUCT();
	struct PORTAKAL_API SceneResourceEntry
	{
		PFIELD();
		Guid ID;
	};

#include "SceneResourceEntry.reflect.h"
}