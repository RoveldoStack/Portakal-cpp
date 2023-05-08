#include "ShaderAssetSerializer.h"

#include <Runtime/Yaml/Yaml.h>
#include <Runtime/Resource/Shader/ShaderResource.h>
#include <Runtime/Resource/Shader/ShaderResourceDescriptor.h>


namespace Portakal
{
	void ShaderAssetSerializer::SerializeToEditor(const ResourceSubObject* pObject, ByteBlock& outBlock)
	{
		/*
		* Get shader
		*/
		ShaderResource* pShader = (ShaderResource*)pObject;

		ShaderResourceDescriptor descriptor = {};
		descriptor.EntryPoint = pShader->GetEntryPoint();
		descriptor.Source = pShader->GetSource();
		descriptor.Stage = pShader->GetStage();

		const String yamlContent = Yaml::ToYaml<ShaderResourceDescriptor>(&descriptor);
		outBlock.Copy(yamlContent.GetSource(), yamlContent.GetCursor());
	}
	void ShaderAssetSerializer::SerializeToPackage(const ResourceSubObject* pObject, ByteBlock& outBlock)
	{

	}
}