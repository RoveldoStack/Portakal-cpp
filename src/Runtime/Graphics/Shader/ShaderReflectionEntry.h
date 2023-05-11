#pragma once
#include <Runtime/Containers/String.h>
#include <Runtime/Graphics/Pipeline/Resource/PipelineResourceType.h>
#include <Runtime/Graphics/Shader/ShaderResourceType.h>
#include <Runtime/Graphics/Shader/ShaderReflectionBufferParameter.h>

namespace Portakal
{
	struct PORTAKAL_API ShaderReflectionEntry
	{
		String Name;
		ShaderResourceType Type;
		unsigned int SizeInBytes;
		Array<ShaderReflectionBufferParameter> BufferParameters;
	};
}