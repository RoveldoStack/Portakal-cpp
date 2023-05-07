#pragma once
#include <Runtime/Containers/String.h>
#include <Runtime/Containers/Guid.h>
#include <Runtime/Containers/Array.h>
#include <Runtime/Reflection/Reflection.h>
namespace Portakal
{
	/// <summary>
	/// Available component field types
	/// </summary>
	enum class PORTAKAL_API SceneComponentFieldType : unsigned int
	{
		Raw,
		Entity,
		Component,
		Resource
	};

	/// <summary>
	/// Represents a single resource entry inside the scene
	/// </summary>
	struct PORTAKAL_API SceneResourceEntry
	{
		Guid ID;
	};

	/// <summary>
	/// Represents a single aspect entry inside the scene
	/// </summary>
	struct PORTAKAL_API SceneAspectEntry
	{
		String TypeName;
	};

	/// <summary>
	/// Represents a single component field entry inside the scene
	/// </summary>
	struct PORTAKAL_API SceneComponentFieldEntry
	{
		String FieldName;
		SceneComponentFieldType Type;
		String Content;
	};

	/// <summary>
	/// Represents a single component entry inside the scene
	/// </summary>
	struct PORTAKAL_API SceneComponentEntry
	{
		String TypeName;
		String TagName;
		Guid ID;
		Array<SceneComponentFieldEntry> Fields;
	};

	/// <summary>
	/// Represents a single entity entry inside the scene
	/// </summary>
	struct PORTAKAL_API SceneEntityEntry
	{
		String TagName;
		Guid ID;
		Array<SceneComponentEntry> Components;
	};

	

	/// <summary>
	/// A descriptor for the scene, one can serialize scene into a scene descriptor and later can create a scene from it
	/// </summary>
	struct PORTAKAL_API SceneDescriptor : public Class
	{
		GENERATE_CLASS(SceneDescriptor);

		SceneDescriptor() = default;
		~SceneDescriptor() = default;

		Array<SceneResourceEntry> Resources;
		Array<SceneAspectEntry> Aspects;
		Array<SceneEntityEntry> Entities;
	};

#include "SceneDescriptor.reflect.h"
}