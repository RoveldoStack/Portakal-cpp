#pragma once
#include <Runtime/Reflection/Reflection.h>

namespace Portakal
{
	/// <summary>
	/// Represents a single aspect entry inside the scene
	/// </summary>
	PSTRUCT();
	struct PORTAKAL_API SceneAspectEntry
	{
		PFIELD();
		String TypeName;
	};

#include "SceneAspectEntry.reflect.h"
}