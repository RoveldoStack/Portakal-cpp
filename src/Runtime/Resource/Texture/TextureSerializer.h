#pragma once
#include <Runtime/Resource/Texture/TextureResource.h>
#include <Runtime/Resource/IResourceSerializer.h>
#include <Runtime/Resource/CustomResourceSerializerAttribute.h>

namespace Portakal
{
	PCLASS_ATTRIBUTE(CustomResourceSerializerAttribute, "texture");
	PCLASS();
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


#include "TextureSerializer.reflect.h"
}