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
			return new Scene();
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
		Scene* pScene = new Scene(descriptor);

		return pScene;
	}
	ResourceSubObject* SceneSerializer::DeserializeCompressed(const ByteBlock& block)
	{
		return nullptr;
	}
}