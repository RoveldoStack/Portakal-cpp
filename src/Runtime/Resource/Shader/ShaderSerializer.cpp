#include "ShaderSerializer.h"
#include <Runtime/Yaml/Yaml.h>
#include <Runtime/Resource/Shader/ShaderObject.h>
#include <Runtime/Resource/Shader/ShaderObjectDescriptor.h>
#include <Runtime/Yaml/Yaml.h>
#include <Runtime/Assert/Assert.h>

namespace Portakal
{
	ResourceSubObject* ShaderSerializer::Deserialize(const ByteBlock& block)
	{
		/*
		* Validate if it's a default or invalid shader object
		*/
		if (block.GetBlockSizeInBytes() == 0)
		{
			return new ShaderObject();
		}

		/*
		* Get yaml bytes as string
		*/
		String yaml((const char*)block.GetBlockDataPtr(), block.GetBlockSizeInBytes());

		/*
		* Deserialize yaml into descriptor
		*/
		ShaderObjectDescriptor descriptor = {};
		ASSERT(Yaml::ToObject<ShaderObjectDescriptor>(yaml, &descriptor), "ShaderSerializer", "Failed to read from yaml");

		/*
		* Create shader
		*/
		ShaderObject* pShader = new ShaderObject();
		pShader->Compile(descriptor.EntryPoint, descriptor.Source, descriptor.Stage);

		return pShader;
	}
	ResourceSubObject* ShaderSerializer::DeserializeCompressed(const ByteBlock& block)
	{
		return nullptr;
	}
}