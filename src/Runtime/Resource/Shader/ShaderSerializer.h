#pragma once
#include <Runtime/Resource/IResourceSerializer.h>
#include <Runtime/Resource/CustomResourceSerializerAttribute.h>

namespace Portakal
{
	CLASS_ATTRIBUTE(CustomResourceSerializerAttribute, "shader");
	class PORTAKAL_API ShaderSerializer : public IResourceSerializer
	{
		GENERATE_CLASS(ShaderSerializer);
	public:
		ShaderSerializer() = default;
		~ShaderSerializer() = default;

	private:
		// Inherited via IResourceSerializer
		virtual ResourceSubObject* Deserialize(const ByteBlock& block) override;
		virtual ResourceSubObject* DeserializeCompressed(const ByteBlock& block) override;

	};

#include "ShaderSerializer.reflect.h"
}