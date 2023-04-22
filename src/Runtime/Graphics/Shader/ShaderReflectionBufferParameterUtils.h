#pragma once
#include <Runtime/Graphics/Shader/ShaderReflectionBufferParameterType.h>
#include <Runtime/Containers/String.h>

namespace Portakal
{
	class PORTAKAL_API ShaderReflectionBufferParameterUtils
	{
	public:
		FORCEINLINE static ShaderReflectionBufferParameterType GetType(const String& str);
	public:
		ShaderReflectionBufferParameterUtils() = delete;
		~ShaderReflectionBufferParameterUtils() = delete;
	};
}