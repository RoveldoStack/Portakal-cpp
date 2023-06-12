#include "DX11ShaderReflectionUtils.h"

namespace Portakal
{
	InputElementDataFormat DX11ShaderReflectionUtils::GetFormat(const D3D_REGISTER_COMPONENT_TYPE componentType, const Byte mask)
	{
		/*
		* Catch base input
		*/
		InputElementDataFormat format = {};

		switch (componentType)
		{
			case D3D_REGISTER_COMPONENT_UNKNOWN:
			{
				format = InputElementDataFormat::Float1;
				break;
			}
			case D3D_REGISTER_COMPONENT_UINT32:
			{
				format = InputElementDataFormat::UInt1;
				break;
			}
			case D3D_REGISTER_COMPONENT_SINT32:
			{
				format = InputElementDataFormat::Int1;
				break;
			}
			case D3D_REGISTER_COMPONENT_FLOAT32:
			{
				format = InputElementDataFormat::Float1;
				break;
			}
			default:
				break;
		}

		/*
		* Catch mask
		*/
		if (mask <= 3)
			format = (InputElementDataFormat)((unsigned char)format + 1);
		else if (mask <= 7)
			format = (InputElementDataFormat)((unsigned char)format + 2);
		else if (mask <= 15)
			format = (InputElementDataFormat)((unsigned char)format + 3);

		return format;
	}
	InputElementSemantic DX11ShaderReflectionUtils::GetSemantic(const String& semantic)
	{
		if (semantic == "POSITION")
			return InputElementSemantic::Position;
		else if (semantic == "TEXCOORD")
			return InputElementSemantic::TextureCoordinate;
		else if (semantic == "NORMAL")
			return InputElementSemantic::Normal;
		else if (semantic == "COLOR")
			return InputElementSemantic::Color;
		
		return InputElementSemantic::Color;
	}
}