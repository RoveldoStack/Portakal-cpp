#include "DXGIUtils.h"

namespace Portakal
{
	DXGI_FORMAT DXGIUtils::GetTextureFormat(const TextureFormat format)
	{
		switch (format)
		{
			case Portakal::TextureFormat::None:
				return DXGI_FORMAT_UNKNOWN;
			case Portakal::TextureFormat::R8_G8_B8_A8_UNorm:
				return DXGI_FORMAT_R8G8B8A8_UNORM;
			case Portakal::TextureFormat::B8_G8_R8_A8_UNorm:
				return DXGI_FORMAT_B8G8R8A8_UNORM;
			case Portakal::TextureFormat::R8_UNorm:
				return DXGI_FORMAT_R8_UNORM;
			case Portakal::TextureFormat::R16_UNorm:
				return DXGI_FORMAT_R16_UNORM;;
			case Portakal::TextureFormat::R32_G32_B32_A32_Float:
				return DXGI_FORMAT_R32G32B32A32_FLOAT;
			case Portakal::TextureFormat::R32_Float:
				return DXGI_FORMAT_R32_FLOAT;
			case Portakal::TextureFormat::BC3_UNorm:
				return DXGI_FORMAT_BC3_UNORM;
			case Portakal::TextureFormat::D24_UNorm_S8_UInt:
				return DXGI_FORMAT_D24_UNORM_S8_UINT;
			case Portakal::TextureFormat::D32_Float_S8_UInt:
				return DXGI_FORMAT_D32_FLOAT_S8X24_UINT;
			case Portakal::TextureFormat::R32_G32_B32_A32_UInt:
				return DXGI_FORMAT_R32G32B32A32_UINT;
			case Portakal::TextureFormat::R8_G8_SNorm:
				return DXGI_FORMAT_R8G8_SNORM;
			case Portakal::TextureFormat::BC1_Rgb_UNorm:
				return DXGI_FORMAT_BC1_UNORM;
			case Portakal::TextureFormat::BC1_Rgba_UNorm:
				return DXGI_FORMAT_BC1_UNORM;
			case Portakal::TextureFormat::BC2_UNorm:
				return DXGI_FORMAT_BC2_UNORM;
			case Portakal::TextureFormat::R10_G10_B10_A2_UNorm:
				return DXGI_FORMAT_R10G10B10A2_UNORM;
			case Portakal::TextureFormat::R10_G10_B10_A2_UInt:
				return DXGI_FORMAT_R10G10B10A2_UINT;
			case Portakal::TextureFormat::R11_G11_B10_Float:
				return DXGI_FORMAT_R11G11B10_FLOAT;
			case Portakal::TextureFormat::R8_SNorm:
				return DXGI_FORMAT_R8_SNORM;
			case Portakal::TextureFormat::R8_UInt:
				return DXGI_FORMAT_R8_UINT;
			case Portakal::TextureFormat::R8_SInt:
				return DXGI_FORMAT_R8_SINT;
			case Portakal::TextureFormat::R16_SNorm:
				return DXGI_FORMAT_R16_SNORM;
			case Portakal::TextureFormat::R16_UInt:
				return DXGI_FORMAT_R16_UINT;
			case Portakal::TextureFormat::R16_SInt:
				return DXGI_FORMAT_R16_SINT;
			case Portakal::TextureFormat::R16_Float:
				return DXGI_FORMAT_R16_FLOAT;
			case Portakal::TextureFormat::R32_UInt:
				return DXGI_FORMAT_R32_UINT;
			case Portakal::TextureFormat::R32_SInt:
				return DXGI_FORMAT_R32_SINT;
			case Portakal::TextureFormat::R8_G8_UNorm:
				return DXGI_FORMAT_R8G8_UNORM;
			case Portakal::TextureFormat::R8_G8_UInt:
				return DXGI_FORMAT_R8G8_UINT;
			case Portakal::TextureFormat::R8_G8_SInt:
				return DXGI_FORMAT_R8G8_SINT;
			case Portakal::TextureFormat::R16_G16_UNorm:
				return DXGI_FORMAT_R16G16_UNORM;
			case Portakal::TextureFormat::R16_G16_SNorm:
				return DXGI_FORMAT_R16G16_SNORM;
			case Portakal::TextureFormat::R16_G16_UInt:
				return DXGI_FORMAT_R16G16_UINT;
			case Portakal::TextureFormat::R16_G16_SInt:
				return DXGI_FORMAT_R16G16_SINT;
			case Portakal::TextureFormat::R16_G16_Float:
				return DXGI_FORMAT_R16G16_FLOAT;
			case Portakal::TextureFormat::R32_G32_UInt:
				return DXGI_FORMAT_R32G32_UINT;
			case Portakal::TextureFormat::R32_G32_SInt:
				return DXGI_FORMAT_R32G32_UINT;
			case Portakal::TextureFormat::R32_G32_Float:
				return DXGI_FORMAT_R32G32_FLOAT;
			case Portakal::TextureFormat::R8_G8_B8_A8_SNorm:
				return DXGI_FORMAT_R8G8B8A8_SNORM;
			case Portakal::TextureFormat::R8_G8_B8_A8_UInt:
				return DXGI_FORMAT_R8G8B8A8_UINT;
			case Portakal::TextureFormat::R8_G8_B8_A8_SInt:
				return DXGI_FORMAT_R8G8B8A8_SINT;
			case Portakal::TextureFormat::R16_G16_B16_A16_UNorm:
				return DXGI_FORMAT_R16G16B16A16_UNORM;
			case Portakal::TextureFormat::R16_G16_B16_A16_SNorm:
				return DXGI_FORMAT_R16G16B16A16_SNORM;
			case Portakal::TextureFormat::R16_G16_B16_A16_UInt:
				return DXGI_FORMAT_R16G16B16A16_UINT;
			case Portakal::TextureFormat::R16_G16_B16_A16_SInt:
				return DXGI_FORMAT_R16G16B16A16_SINT;
			case Portakal::TextureFormat::R16_G16_B16_A16_Float:
				return DXGI_FORMAT_R16G16B16A16_FLOAT;
			case Portakal::TextureFormat::R32_G32_B32_A32_SInt:
				return DXGI_FORMAT_R32G32B32A32_SINT;
			case Portakal::TextureFormat::ETC2_R8_G8_B8_UNorm:
				return DXGI_FORMAT_UNKNOWN;
			case Portakal::TextureFormat::ETC2_R8_G8_B8_A1_UNorm:
				return DXGI_FORMAT_UNKNOWN;
			case Portakal::TextureFormat::ETC2_R8_G8_B8_A8_UNorm:
				return DXGI_FORMAT_UNKNOWN;
			case Portakal::TextureFormat::BC4_UNorm:
				return DXGI_FORMAT_BC4_UNORM;
			case Portakal::TextureFormat::BC4_SNorm:
				return DXGI_FORMAT_BC4_SNORM;
			case Portakal::TextureFormat::BC5_UNorm:
				return DXGI_FORMAT_BC5_UNORM;
			case Portakal::TextureFormat::BC5_SNorm:
				return DXGI_FORMAT_BC5_SNORM;
			case Portakal::TextureFormat::BC7_UNorm:
				return DXGI_FORMAT_BC7_UNORM;
			case Portakal::TextureFormat::R8_G8_B8_A8_UNorm_SRgb:
				return DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
			case Portakal::TextureFormat::B8_G8_R8_A8_UNorm_SRgb:
				return DXGI_FORMAT_B8G8R8A8_UNORM_SRGB;
			case Portakal::TextureFormat::BC1_Rgb_UNorm_SRgb:
				return DXGI_FORMAT_BC1_UNORM_SRGB;
			case Portakal::TextureFormat::BC1_Rgba_UNorm_SRgb:
				return DXGI_FORMAT_BC1_UNORM_SRGB;
			case Portakal::TextureFormat::BC2_UNorm_SRgb:
				return DXGI_FORMAT_BC2_UNORM_SRGB;
			case Portakal::TextureFormat::BC3_UNorm_SRgb:
				return DXGI_FORMAT_BC3_UNORM_SRGB;
			case Portakal::TextureFormat::BC7_UNorm_SRgb:
				return DXGI_FORMAT_BC7_UNORM_SRGB;
			default:
				return DXGI_FORMAT_UNKNOWN;
		}
	}
	DXGI_FORMAT DXGIUtils::GetInputElementFormat(InputElementDataFormat type)
	{
		switch (type)
		{
			case Portakal::InputElementDataFormat::Float1:
				return DXGI_FORMAT_R32_FLOAT;
			case Portakal::InputElementDataFormat::Float2:
				return DXGI_FORMAT_R32G32_FLOAT;
			case Portakal::InputElementDataFormat::Float3:
				return DXGI_FORMAT_R32G32B32_FLOAT;
			case Portakal::InputElementDataFormat::Float4:
				return DXGI_FORMAT_R32G32B32A32_FLOAT;
			case Portakal::InputElementDataFormat::Byte2_Norm:
				return DXGI_FORMAT_R8G8_UNORM;
			case Portakal::InputElementDataFormat::Byte2:
				return DXGI_FORMAT_R8G8B8A8_UINT;
			case Portakal::InputElementDataFormat::Byte4_Norm:
				return DXGI_FORMAT_R8G8B8A8_UNORM;
			case Portakal::InputElementDataFormat::Byte4:
				return DXGI_FORMAT_R8G8B8A8_UINT;
			case Portakal::InputElementDataFormat::SByte2_Norm:
				return DXGI_FORMAT_R8G8_SNORM;
			case Portakal::InputElementDataFormat::SByte2:
				return DXGI_FORMAT_R8G8_SINT;
			case Portakal::InputElementDataFormat::SByte4_Norm:
				return DXGI_FORMAT_R8G8B8A8_UNORM;
			case Portakal::InputElementDataFormat::SByte4:
				break;
			case Portakal::InputElementDataFormat::UShort2_Norm:
				break;
			case Portakal::InputElementDataFormat::UShort2:
				break;
			case Portakal::InputElementDataFormat::UShort4_Norm:
				break;
			case Portakal::InputElementDataFormat::UShort4:
				break;
			case Portakal::InputElementDataFormat::Short2_Norm:
				break;
			case Portakal::InputElementDataFormat::Short2:
				break;
			case Portakal::InputElementDataFormat::Short4_Norm:
				break;
			case Portakal::InputElementDataFormat::Short4:
				break;
			case Portakal::InputElementDataFormat::UInt1:
				break;
			case Portakal::InputElementDataFormat::UInt2:
				break;
			case Portakal::InputElementDataFormat::UInt3:
				break;
			case Portakal::InputElementDataFormat::UInt4:
				break;
			case Portakal::InputElementDataFormat::Int1:
				break;
			case Portakal::InputElementDataFormat::Int2:
				break;
			case Portakal::InputElementDataFormat::Int3:
				break;
			case Portakal::InputElementDataFormat::Int4:
				break;
			case Portakal::InputElementDataFormat::Half1:
				break;
			case Portakal::InputElementDataFormat::Half2:
				break;
			case Portakal::InputElementDataFormat::Half4:
				break;
			default:
				break;
		}
	}
}