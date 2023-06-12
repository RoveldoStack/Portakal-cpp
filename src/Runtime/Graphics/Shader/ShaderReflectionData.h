#pragma once
#include <Runtime/Containers/Array.h>
#include <Runtime/Graphics/Shader/ShaderReflectionResource.h>
#include <Runtime/Graphics/Shader/ShaderReflectionInputOutputData.h>
namespace Portakal
{
	struct PORTAKAL_API ShaderReflectionData
	{
		Array<ShaderReflectionResource> Resources;
		Array<ShaderReflectionInputOutputData> Inputs;
		Array<ShaderReflectionInputOutputData> Outputs;
	};
}
