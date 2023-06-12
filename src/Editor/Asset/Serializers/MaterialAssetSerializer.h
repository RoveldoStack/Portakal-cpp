#pragma once
#include <Runtime/Resource/Material/MaterialResource.h>
#include <Editor/Asset/IAssetSerializer.h>
#include <Editor/Asset/CustomAssetSerializerAttribute.h>

namespace Portakal
{
	PCLASS_ATTRIBUTE(CustomAssetSerializerAttribute, "material");
	PCLASS();
	class PORTAKAL_API MaterialAssetSerializer : public IAssetSerializer
	{
		GENERATE_CLASS(MaterialAssetSerializer);
	public:
		MaterialAssetSerializer() = default;
		~MaterialAssetSerializer() = default;
	private:

		// Inherited via IAssetSerializer
		virtual void SerializeToEditor(const ResourceSubObject* pObject, ByteBlock& outBlock) override;
		virtual void SerializeToPackage(const ResourceSubObject* pObject, ByteBlock& outBlock) override;
	};

#include "MaterialAssetSerializer.reflect.h"
}