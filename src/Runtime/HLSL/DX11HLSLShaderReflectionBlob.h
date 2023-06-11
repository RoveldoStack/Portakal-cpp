#pragma once
#include <Runtime/Graphics/Shader/ShaderReflectionBlob.h>
#include <Runtime/Memory/ByteBlock.h>

namespace Portakal
{
	class PORTAKAL_API DX11HLSLShaderReflectionBlob : public ShaderReflectionBlob
	{
	public:
		DX11HLSLShaderReflectionBlob(const ByteBlock& byteBlock);
		~DX11HLSLShaderReflectionBlob() = default;
	};
}