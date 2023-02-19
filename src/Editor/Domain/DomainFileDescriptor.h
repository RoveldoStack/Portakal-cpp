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
		String ResourceType;

		/// <summary>
		/// Source file path
		/// </summary>
		String SourceFile;

		/// <summary>
		/// Unique id
		/// </summary>
		Guid ID;
	};

	START_GENERATE_TYPE(DomainFileDescriptor);
	START_TYPE_PROPERTIES(DomainFileDescriptor);
	END_TYPE_PROPERTIES;
	HAS_DEFAULT_CONSTRUCTOR(DomainFileDescriptor);
	END_GENERATE_TYPE(DomainFileDescriptor);
}