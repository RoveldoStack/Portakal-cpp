#include "SceneSerializer.h"
#include <Runtime/Yaml/Yaml.h>
#include <Runtime/Assert/Assert.h>
#include <Runtime/World/SceneAPI.h>

namespace Portakal
{
	ResourceSubObject* SceneSerializer::Deserialize(const ByteBlock& block)
	{
		/*
		* Validate if it's a default or invalid scene
		*/
		if (block.GetBlockSizeInBytes() == 0)
		{
			return SceneAPI::CreateScene(false);
		}

		/*
		* Get yaml bytes as string
		*/
		String yaml((const char*)block.GetBlockDataPtr(), block.GetBlockSizeInBytes());

		/*
		* Deserialize yaml into scene descriptor
		*/
		SceneDescriptor descriptor = {};
		ASSERT(Yaml::ToObject<SceneDescriptor>(yaml, &descriptor), "SceneSerializer", "Failed to read from yaml");

		/*
		* Create Scene
		*/
		Scene* pScene = SceneAPI::CreateScene(descriptor,false);

		return pScene;
	}
	ResourceSubObject* SceneSerializer::DeserializeCompressed(const ByteBlock& block)
	{
		return nullptr;
	}
}