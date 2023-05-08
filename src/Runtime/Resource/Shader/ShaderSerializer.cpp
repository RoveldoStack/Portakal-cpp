#include "ShaderSerializer.h"
#include <Runtime/Yaml/Yaml.h>
#include <Runtime/Resource/Shader/ShaderResource.h>
#include <Runtime/Resource/Shader/ShaderResourceDescriptor.h>
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
			return new ShaderResource();
		}

		/*
		* Get yaml bytes as string
		*/
		String yaml((const char*)block.GetBlockDataPtr(), block.GetBlockSizeInBytes());

		/*
		* Deserialize yaml into descriptor
		*/
		ShaderResourceDescriptor descriptor = {};
		Yaml::ToObject<ShaderResourceDescriptor>(yaml, &descriptor);

		/*
		* Create shader
		*/
		ShaderResource* pShader = new ShaderResource();
		pShader->Compile(descriptor.EntryPoint, descriptor.Source, descriptor.Stage);

		return pShader;
	}
	ResourceSubObject* ShaderSerializer::DeserializeCompressed(const ByteBlock& block)
	{
		return nullptr;
	}
}