#include "ShaderReflectionBlob.h"
#include <Runtime/HLSL/HLSLShaderReflectionBlob.h>

namespace Portakal
{
	ShaderReflectionBlob* ShaderReflectionBlob::Create(const ByteBlock& byteBlock)
	{
		return new HLSLShaderReflectionBlob(byteBlock);
	}
}