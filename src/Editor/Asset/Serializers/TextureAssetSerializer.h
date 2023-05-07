#pragma once
#include <Editor/Asset/IAssetSerializer.h>
#include <Editor/Asset/CustomAssetSerializerAttribute.h>

namespace Portakal
{
	PCLASS_ATTRIBUTE(CustomAssetSerializerAttribute, "texture");
	PCLASS();
	class PORTAKAL_API TextureAssetSerializer : public IAssetSerializer
	{
		GENERATE_CLASS(TextureAssetSerializer);
	public:
		TextureAssetSerializer() = default;
		~TextureAssetSerializer() = default;

		virtual void SerializeToEditor(const ResourceSubObject* pObject, ByteBlock& outBlock) override;
		virtual void SerializeToPackage(const ResourceSubObject* pObject, ByteBlock& outBlock) override;

	};
#include "TextureAssetSerializer.reflect.h"
}