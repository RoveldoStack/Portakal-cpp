#pragma once
#include <Runtime/Containers/String.h>
#include <Runtime/Graphics/Shader/ShaderReflectionBufferParameterType.h>
namespace Portakal
{
	struct PORTAKAL_API ShaderReflectionBufferParameter
	{
		String Name;
		ShaderReflectionBufferParameterType Type;
	};
}