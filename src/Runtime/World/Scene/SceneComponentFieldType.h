#pragma once
#include <Runtime/Reflection/Reflection.h>

namespace Portakal
{
	/// <summary>
	/// Available component field types
	/// </summary>
	PENUM();
	enum class PORTAKAL_API SceneComponentFieldType : long long
	{
		Raw,
		Entity,
		Component,
		Resource
	};

#include "SceneComponentFieldType.reflect.h"
}