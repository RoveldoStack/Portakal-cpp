#pragma once
#include <Runtime/Reflection/Reflection.h>
#include <Runtime/World/Scene/SceneComponentFieldEntry.h>
#include <Runtime/Containers/Guid.h>
#include <Runtime/World/Scene/SceneComponentEntry.h>
namespace Portakal
{
	/// <summary>
	/// Represents a single entity entry inside the scene
	/// </summary>
	PSTRUCT();
	struct PORTAKAL_API SceneEntityEntry
	{
		PFIELD();
		String TagName;
		PFIELD();
		Guid ID;
		PFIELD();
		Array<SceneComponentEntry> Components;
	};

#include "SceneEntityEntry.reflect.h"
}