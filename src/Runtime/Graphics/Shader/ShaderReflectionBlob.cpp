#include "ShaderReflectionBlob.h"
#include <Runtime/HLSL/HLSLShaderReflectionBlob.h>

namespace Portakal
{
	ShaderReflectionBlob* ShaderReflectionBlob::Create(const String& source,const ShadingLanguage language)
	{
		switch (language)
		{
			case Portakal::ShadingLanguage::Unknown:
				return nullptr;
			case Portakal::ShadingLanguage::GLSL:
				return nullptr;
			case Portakal::ShadingLanguage::HLSL:
				return new HLSLShaderReflectionBlob(source);
			default:
				return nullptr;
		}

	}
}