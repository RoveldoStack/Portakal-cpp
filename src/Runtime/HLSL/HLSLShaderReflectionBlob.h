#pragma once
#include <Runtime/Graphics/Shader/ShaderReflectionBlob.h>

namespace Portakal
{
	class PORTAKAL_API HLSLShaderReflectionBlob : public ShaderReflectionBlob
	{
	public:

		HLSLShaderReflectionBlob(const String& source);
		~HLSLShaderReflectionBlob() = default;

		// Inherited via ShaderReflectionBlob
		virtual ShadingLanguage GetLanguage() const noexcept override { return ShadingLanguage::HLSL; }
	};
}