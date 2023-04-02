#include "SceneAssetSerializer.h"
#include <Runtime/World/Scene.h>
#include <Editor/Asset/Yaml/SceneDescriptorYamlSerializer.h>
#include <Runtime/World/SceneDescriptor.h>
#include <Runtime/Yaml/Yaml.h>
#include <Runtime/Log/Log.h>

namespace Portakal
{
	void SceneAssetSerializer::SerializeToEditor(const ResourceSubObject* pObject, ByteBlock& outBlock)
	{
		/*
		* Get scene
		*/
		Scene* pScene = (Scene*)pObject;

		SceneDescriptor descriptor;
		pScene->GenerateDescriptor(descriptor);

		const String yamlContent = Yaml::ToYaml<SceneDescriptor>(&descriptor);
		outBlock.Copy(yamlContent.GetSource(), yamlContent.GetCursor());
		LOG("SceneAssetSerializer", "Serializing to editor: %s", *yamlContent);
	}
	void SceneAssetSerializer::SerializeToPackage(const ResourceSubObject* pObject, ByteBlock& outBlock)
	{

	}
}