#pragma once
#include <Runtime/Resource/Texture/TextureResource.h>
#include <Runtime/Resource/IResourceSerializer.h>
#include <Runtime/Resource/CustomResourceSerializerAttribute.h>

namespace Portakal
{
	CLASS_ATTRIBUTE(CustomResourceSerializerAttribute, "texture");
	class PORTAKAL_API TextureSerializer : public IResourceSerializer
	{
		GENERATE_CLASS(TextureSerializer);
	public:
		TextureSerializer() = default;
		~TextureSerializer() = default;


		// Inherited via IResourceSerializer
		virtual ResourceSubObject* Deserialize(const ByteBlock& block) override;
		virtual ResourceSubObject* DeserializeCompressed(const ByteBlock& block) override;

	};

	//START_GENERATE_TYPE(TextureSerializer);
	//START_TYPE_PROPERTIES(TextureSerializer);
	//REGISTER_BASE_TYPE(IResourceSerializer);
	//REGISTER_TYPE_ATTRIBUTE(CustomResourceSerializerAttribute, "texture");
	//END_TYPE_PROPERTIES;
	//HAS_DEFAULT_CONSTRUCTOR(TextureSerializer);
	//END_GENERATE_TYPE(TextureSerializer);

#include "TextureSerializer.reflect.h"
}