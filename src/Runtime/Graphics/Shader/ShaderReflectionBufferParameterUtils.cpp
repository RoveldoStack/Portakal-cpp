#include "ShaderReflectionBufferParameterUtils.h"

namespace Portakal
{
	ShaderReflectionBufferParameterType ShaderReflectionBufferParameterUtils::GetType(const String& str)
	{
		if (str == "bool")
			return ShaderReflectionBufferParameterType::Bool;

		if (str == "int")
			return ShaderReflectionBufferParameterType::Int1;
		if (str == "int2")
			return ShaderReflectionBufferParameterType::Int2;
		if (str == "int3")
			return ShaderReflectionBufferParameterType::Int3;
		if (str == "int4")
			return ShaderReflectionBufferParameterType::Int4;

		if (str == "uint")
			return ShaderReflectionBufferParameterType::UInt1;
		if (str == "uint2")
			return ShaderReflectionBufferParameterType::UInt2;
		if (str == "uint3")
			return ShaderReflectionBufferParameterType::UInt3;
		if (str == "uint4")
			return ShaderReflectionBufferParameterType::UInt4;

		if (str == "float")
			return ShaderReflectionBufferParameterType::Float1;
		if (str == "float2")
			return ShaderReflectionBufferParameterType::Float2;
		if (str == "float3")
			return ShaderReflectionBufferParameterType::Float3;
		if (str == "float4")
			return ShaderReflectionBufferParameterType::Float4;

		if (str == "float3x3")
			return ShaderReflectionBufferParameterType::Matrix3x3;
		if (str == "float4x4")
			return ShaderReflectionBufferParameterType::Matrix3x3;

		return ShaderReflectionBufferParameterType::Unknown;
	}
}