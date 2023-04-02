#pragma once
#include <Editor/Asset/IAssetSerializer.h>
#include <Editor/Asset/CustomAssetSerializerAttribute.h>


namespace Portakal
{
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

	START_GENERATE_TYPE(ShaderAssetSerializer);
	START_TYPE_PROPERTIES(ShaderAssetSerializer);
	REGISTER_BASE_TYPE(IAssetSerializer);
	REGISTER_TYPE_ATTRIBUTE(CustomAssetSerializerAttribute, "scene");
	END_TYPE_PROPERTIES;
	HAS_DEFAULT_CONSTRUCTOR(ShaderAssetSerializer);
	END_GENERATE_TYPE(ShaderAssetSerializer);
}