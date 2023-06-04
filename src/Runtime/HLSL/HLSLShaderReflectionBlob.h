#pragma once
#include <Runtime/Graphics/Shader/ShaderReflectionBlob.h>
#include <Runtime/Memory/ByteBlock.h>

namespace Portakal
{
	class PORTAKAL_API HLSLShaderReflectionBlob : public ShaderReflectionBlob
	{
	public:
		HLSLShaderReflectionBlob(const ByteBlock& byteBlock);
		~HLSLShaderReflectionBlob() = default;
	};
}