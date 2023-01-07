#pragma once
#include <Runtime/Containers/String.h>
#include <Runtime/Graphics/ShaderStage.h>

namespace Portakal
{
	class PORTAKAL_API D3DCompilerUtils
	{
	public:
		D3DCompilerUtils() = delete;
		~D3DCompilerUtils() = delete;

		FORCEINLINE static String GetCompilerTarget(const ShaderStage stage, const unsigned int major, const unsigned int minor);
	};
}