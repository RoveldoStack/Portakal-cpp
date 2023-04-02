#pragma once
#include <Runtime/Resource/IResourceSerializer.h>
#include <Runtime/Resource/CustomResourceSerializerAttribute.h>

namespace Portakal
{
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

	START_GENERATE_TYPE(ShaderSerializer);
	START_TYPE_PROPERTIES(ShaderSerializer);
	REGISTER_BASE_TYPE(IResourceSerializer);
	REGISTER_TYPE_ATTRIBUTE(CustomResourceSerializerAttribute,"shader");
	END_TYPE_PROPERTIES;
	HAS_DEFAULT_CONSTRUCTOR(ShaderSerializer);
	END_GENERATE_TYPE(ShaderSerializer);
}