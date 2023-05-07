#pragma once
#include <Editor/Asset/IAssetSerializer.h>
#include <Editor/Asset/CustomAssetSerializerAttribute.h>


namespace Portakal
{
	PCLASS_ATTRIBUTE(CustomAssetSerializerAttribute, "scene");
	PCLASS();
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

#include "SceneAssetSerializer.reflect.h"
}