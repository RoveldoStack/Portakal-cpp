#pragma once
#include <Editor/Asset/IAssetSerializer.h>
#include <Editor/Asset/CustomAssetSerializerAttribute.h>


namespace Portakal
{
	PCLASS_ATTRIBUTE(CustomAssetSerializerAttribute, "shader");
	PCLASS();
	class PORTAKAL_API ShaderAssetSerializer : public IAssetSerializer
	{
		GENERATE_CLASS(ShaderAssetSerializer);
	public:
		ShaderAssetSerializer() = default;
		~ShaderAssetSerializer() = default;

		// Inherited via IAssetSerializer
		virtual void SerializeToEditor(const ResourceSubObject* pObject, ByteBlock& outBlock) override;
		virtual void SerializeToPackage(const ResourceSubObject* pObject, ByteBlock& outBlock) override;

	};

#include "ShaderAssetSerializer.reflect.h"
}