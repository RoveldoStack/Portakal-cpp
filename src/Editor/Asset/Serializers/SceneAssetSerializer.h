#pragma once
#include <Editor/Asset/IAssetSerializer.h>
#include <Editor/Asset/CustomAssetSerializerAttribute.h>


namespace Portakal
{
	class PORTAKAL_API SceneAssetSerializer : public IAssetSerializer
	{
		GENERATE_CLASS(SceneAssetSerializer);
	public:
		SceneAssetSerializer() = default;
		~SceneAssetSerializer() = default;

		// Inherited via IAssetSerializer
		virtual void SerializeToEditor(const ResourceSubObject* pObject, ByteBlock& outBlock) override;
		virtual void SerializeToPackage(const ResourceSubObject* pObject, ByteBlock& outBlock) override;

	};

	START_GENERATE_TYPE(SceneAssetSerializer);
	START_TYPE_PROPERTIES(SceneAssetSerializer);
	REGISTER_BASE_TYPE(IAssetSerializer);
	REGISTER_TYPE_ATTRIBUTE(CustomAssetSerializerAttribute, "scene");
	END_TYPE_PROPERTIES;
	HAS_DEFAULT_CONSTRUCTOR(SceneAssetSerializer);
	END_GENERATE_TYPE(SceneAssetSerializer);
}