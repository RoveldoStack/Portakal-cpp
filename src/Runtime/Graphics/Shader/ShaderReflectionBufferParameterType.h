#pragma once
#include <Runtime/Core/Core.h>

namespace Portakal
{
	enum class PORTAKAL_API ShaderReflectionBufferParameterType
	{
		Unknown,
		Bool,
		Int1,
		Int2,
		Int3,
		Int4,
		UInt1,
		UInt2,
		UInt3,
		UInt4,
		Float1,
		Float2,
		Float3,
		Float4,
		Half1,
		Half2,
		Half3,
		Half4,
		Matrix3x3,
		Matrix4x4
	};
}