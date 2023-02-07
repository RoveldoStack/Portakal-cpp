#pragma once
#include <Runtime/Core/Core.h>
#include <Runtime/Containers/Guid.h>
#include <Runtime/Containers/String.h>
#include <Runtime/Yaml/YamlSerializerAttribute.h>
#include <Runtime/Yaml/YamlSerializer.h>
namespace Portakal
{
	struct PORTAKAL_API DomainFileDescriptor : public Class
	{
		GENERATE_CLASS(DomainFileDescriptor);

		String TypeName;
		Guid ID;
	};

	START_GENERATE_TYPE(DomainFileDescriptor);
	START_TYPE_PROPERTIES(DomainFileDescriptor);
	END_TYPE_PROPERTIES;
	CONCRETE_TYPE(DomainFileDescriptor);
	END_GENERATE_TYPE(DomainFileDescriptor);
}