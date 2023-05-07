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
	struct PORTAKAL_API DomainFileDescriptor : public Class
	{
		GENERATE_CLASS(DomainFileDescriptor);

		/// <summary>
		/// Resource type
		/// </summary>
		FIELD();
		String ResourceType;

		/// <summary>
		/// Source file path
		/// </summary>
		FIELD();
		String SourceFile;

		/// <summary>
		/// Unique id
		/// </summary>
		FIELD();
		Guid ID;
	};

#include "DomainFileDescriptor.reflect.h"
}