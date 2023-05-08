#pragma once
#include <Runtime/Reflection/Reflection.h>
#include <Runtime/Containers/Guid.h>
namespace Portakal
{
	/// <summary>
	/// Represents a single component entry inside the scene
	/// </summary>
	PSTRUCT();
	struct PORTAKAL_API SceneComponentEntry
	{
		PFIELD();
		String TypeName;
		PFIELD();
		String TagName;
		PFIELD();
		Guid ID;
		PFIELD();
		String Content;
	};

#include "SceneComponentEntry.reflect.h"
}