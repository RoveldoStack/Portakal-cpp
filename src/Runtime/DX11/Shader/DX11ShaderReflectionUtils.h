#pragma once
#include <Runtime/Core/Core.h>
#include <Runtime/Graphics/Pipeline/Input/InputElementSemantic.h>
#include <Runtime/Graphics/Pipeline/Input/InputElementDataFormat.h>
#include <Runtime/Containers/String.h>
#include <d3dcommon.h>

namespace Portakal
{
	class PORTAKAL_API DX11ShaderReflectionUtils
	{
	public:
		static InputElementDataFormat GetFormat(const D3D_REGISTER_COMPONENT_TYPE componentType, const Byte mask);
		static InputElementSemantic GetSemantic(const String& semantic);
	public:
		DX11ShaderReflectionUtils() = delete;
		~DX11ShaderReflectionUtils() = delete;
	};
}