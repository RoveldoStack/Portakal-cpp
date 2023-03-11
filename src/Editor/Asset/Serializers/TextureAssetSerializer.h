#pragma once
#include <Editor/Asset/IAssetSerializer.h>
#include <Editor/Asset/CustomAssetSerializerAttribute.h>

namespace Portakal
{
	class PORTAKAL_API TextureAssetSerializer : public IAssetSerializer
	{
		GENERATE_CLASS(TextureAssetSerializer);
	public:
		TextureAssetSerializer() = default;
		~TextureAssetSerializer() = default;

		virtual void SerializeToEditor(const ResourceSubObject* pObject) override;
		virtual void SerializeToPackage(const ResourceSubObject* pObject) override;

	};

	START_GENERATE_TYPE(TextureAssetSerializer);
	START_TYPE_PROPERTIES(TextureAssetSerializer);
	REGISTER_BASE_TYPE(IAssetSerializer);
	REGISTER_TYPE_ATTRIBUTE(CustomAssetSerializerAttribute, "texture");
	END_TYPE_PROPERTIES;
	HAS_DEFAULT_CONSTRUCTOR(TextureAssetSerializer);
	END_GENERATE_TYPE(TextureAssetSerializer);
}