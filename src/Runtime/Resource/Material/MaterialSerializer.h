#pragma once
#include <Runtime/Resource/IResourceSerializer.h>
#include <Runtime/Resource/CustomResourceSerializerAttribute.h>

namespace Portakal
{
	PCLASS_ATTRIBUTE(CustomResourceSerializerAttribute,"material")
	PCLASS();
	class PORTAKAL_API MaterialSerializer : public IResourceSerializer
	{
		GENERATE_CLASS(MaterialSerializer);
	public:
		MaterialSerializer() = default;
		~MaterialSerializer() = default;

	private:

		// Inherited via IResourceSerializer
		virtual ResourceSubObject* Deserialize(const ByteBlock& block) override;
		virtual ResourceSubObject* DeserializeCompressed(const ByteBlock& block) override;
	};

#include "MaterialSerializer.reflect.h"
}