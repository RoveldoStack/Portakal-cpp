#pragma once
#include <Runtime/Graphics/Shader/ShaderReflectionBlob.h>
#include <Runtime/Memory/ByteBlock.h>

namespace Portakal
{
	class PORTAKAL_API DX11ShaderReflectionBlob : public ShaderReflectionBlob
	{
	public:
		DX11ShaderReflectionBlob(const ByteBlock& byteBlock);
		~DX11ShaderReflectionBlob() = default;
	};
}