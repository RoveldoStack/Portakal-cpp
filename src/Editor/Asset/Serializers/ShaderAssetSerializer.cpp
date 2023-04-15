#include "ShaderAssetSerializer.h"

#include <Runtime/Yaml/Yaml.h>
#include <Runtime/Resource/Shader/ShaderObject.h>
#include <Runtime/Resource/Shader/ShaderObjectDescriptor.h>


namespace Portakal
{
	void ShaderAssetSerializer::SerializeToEditor(const ResourceSubObject* pObject, ByteBlock& outBlock)
	{
		/*
		* Get shader
		*/
		ShaderObject* pShader = (ShaderObject*)pObject;

		ShaderObjectDescriptor descriptor = {};
		descriptor.EntryPoint = pShader->GetEntryPoint();
		descriptor.Source = pShader->GetSource();
		descriptor.Stage = pShader->GetStage();

		const String yamlContent = Yaml::ToYaml<ShaderObjectDescriptor>(&descriptor);
		outBlock.Copy(yamlContent.GetSource(), yamlContent.GetCursor());
	}
	void ShaderAssetSerializer::SerializeToPackage(const ResourceSubObject* pObject, ByteBlock& outBlock)
	{

	}
}