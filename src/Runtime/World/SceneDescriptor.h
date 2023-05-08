#pragma once
#include <Runtime/Containers/String.h>
#include <Runtime/Containers/Guid.h>
#include <Runtime/Containers/Array.h>
#include <Runtime/Reflection/Reflection.h>
#include <Runtime/World/Scene/SceneResourceEntry.h>
#include <Runtime/World/Scene/SceneAspectEntry.h>
#include <Runtime/World/Scene/SceneEntityEntry.h>

namespace Portakal
{

	/// <summary>
	/// A descriptor for the scene, one can serialize scene into a scene descriptor and later can create a scene from it
	/// </summary>
	PSTRUCT()
	struct PORTAKAL_API SceneDescriptor
	{
		SceneDescriptor() = default;
		~SceneDescriptor() = default;

		PFIELD();
		Array<SceneResourceEntry> Resources;
		PFIELD();
		Array<SceneAspectEntry> Aspects;
		PFIELD();
		Array<SceneEntityEntry> Entities;
	};

#include "SceneDescriptor.reflect.h"
}