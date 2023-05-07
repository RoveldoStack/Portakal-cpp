#pragma once
#include <Editor/Asset/IAssetSerializer.h>
#include <Editor/Asset/CustomAssetSerializerAttribute.h>

namespace Portakal
{
	PCLASS_ATTRIBUTE(CustomAssetSerializerAttribute, "simple-text");
	PCLASS();
	class PORTAKAL_API TextAssetSerializer : public IAssetSerializer
	{
		GENERATE_CLASS(TextAssetSerializer);
	public:
		TextAssetSerializer() = default;
		~TextAssetSerializer() = default;

		// Inherited via IAssetSerializer
		virtual void SerializeToEditor(const ResourceSubObject* pObject, ByteBlock& outBlock) override;
		virtual void SerializeToPackage(const ResourceSubObject* pObject, ByteBlock& outBlock) override;
	};

#include "TextAssetSerializer.reflect.h"

}