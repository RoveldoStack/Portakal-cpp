#pragma once
#include <Runtime/Reflection/Reflection.h>
#include <Runtime/World/Scene/SceneComponentFieldType.h>

namespace Portakal
{

	/// <summary>
	/// Represents a single component field entry inside the scene
	/// </summary>
	PSTRUCT();
	struct PORTAKAL_API SceneComponentFieldEntry
	{
		PFIELD();
		String FieldName;
		PFIELD();
		SceneComponentFieldType Type;
		PFIELD();
		String Content;
	};

#include "SceneComponentFieldEntry.reflect.h"
}