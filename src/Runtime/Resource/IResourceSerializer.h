#pragma once
#include <Runtime/Core/Core.h>
#include <Runtime/Memory/ByteBlock.h>
#include <Runtime/Reflection/Reflection.h>

namespace Portakal
{
	class ResourceSubObject;
	class PORTAKAL_API IResourceSerializer : public Class
	{
		GENERATE_CLASS(IResourceSerializer,Virtual);
	public:
		IResourceSerializer() = default;
		~IResourceSerializer() = default;

		virtual ResourceSubObject* Deserialize(const ByteBlock& block) = 0;
		virtual ResourceSubObject* DeserializeCompressed(const ByteBlock& block) = 0;
	};

	//START_GENERATE_TYPE(IResourceSerializer);
	//START_TYPE_PROPERTIES(IResourceSerializer);
	//END_TYPE_PROPERTIES;
	//NO_DEFAULT_CONSTRUCTOR;
	//END_GENERATE_TYPE(IResourceSerializer);

#include "IResourceSerializer.reflect.h"

}