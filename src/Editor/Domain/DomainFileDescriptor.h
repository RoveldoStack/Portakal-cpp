#pragma once
#include <Runtime/Core/Core.h>
#include <Runtime/Containers/Guid.h>
#include <Runtime/Containers/String.h>
#include <Runtime/Yaml/YamlSerializerAttribute.h>
#include <Runtime/Yaml/IYamlSerializer.h>
namespace Portakal
{
	/// <summary>
	/// Domain file descriptor for yaml serialization
	/// </summary>
	PSTRUCT();
	struct PORTAKAL_API DomainFileDescriptor
	{
		/// <summary>
		/// Resource type
		/// </summary>
		PFIELD();
		String ResourceType;

		/// <summary>
		/// Source file path
		/// </summary>
		PFIELD();
		String SourceFile;

		/// <summary>
		/// Unique id
		/// </summary>
		PFIELD();
		Guid ID;
	};

#include "DomainFileDescriptor.reflect.h"
}