#include "DX12SamplerUtils.h"
#include <Runtime/Assert/Assert.h>

namespace Portakal
{
	D3D12_TEXTURE_ADDRESS_MODE DX12SamplerUtils::GetWrapMode(const SamplerAddress address)
	{
		switch (address)
		{
			case Portakal::SamplerAddress::Wrap:
				return D3D12_TEXTURE_ADDRESS_MODE_MIRROR;
			case Portakal::SamplerAddress::Mirror:
				return D3D12_TEXTURE_ADDRESS_MODE_MIRROR_ONCE;
			case Portakal::SamplerAddress::Clamp:
				return D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
			case Portakal::SamplerAddress::Border:
				return D3D12_TEXTURE_ADDRESS_MODE_BORDER;
			default:
				ASSERT(false, "DX12SamplerUtils", "Invalid SamplerWrapMode!");
				break;
		}
	}
	D3D12_STATIC_BORDER_COLOR DX12SamplerUtils::GetBorderColor(const SamplerBorderColor color)
	{
		switch (color)
		{
			case Portakal::SamplerBorderColor::TransparentBlack:
				return D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;
			case Portakal::SamplerBorderColor::OpaqueBlack:
				return D3D12_STATIC_BORDER_COLOR_OPAQUE_BLACK;
			case Portakal::SamplerBorderColor::OpaqueWhite:
				return D3D12_STATIC_BORDER_COLOR_OPAQUE_WHITE;
			default:
				ASSERT(false, "DX12SamplerUtils", "Invalid SamplerBorderColor!");
				break;
		}
	}

	D3D12_FILTER DX12SamplerUtils::GetFilter( SamplerFiltering filter)
	{
		switch (filter)
		{
		case Portakal::SamplerFiltering::MinPoint_MagPoint_MipPoint:
			return D3D12_FILTER_MIN_MAG_MIP_POINT;
		case Portakal::SamplerFiltering::MinPoint_MagPoint_MipLinear:
			return D3D12_FILTER_MIN_MAG_POINT_MIP_LINEAR;
		case Portakal::SamplerFiltering::MinPoint_MagLinear_MipPoint:
			return D3D12_FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT;
		case Portakal::SamplerFiltering::MinPoint_MagLinear_MipLinear:
			return D3D12_FILTER_MIN_POINT_MAG_MIP_LINEAR;
		case Portakal::SamplerFiltering::MinLinear_MagPoint_MipPoint:
			return D3D12_FILTER_MIN_LINEAR_MAG_MIP_POINT;
		case Portakal::SamplerFiltering::MinLinear_MagPoint_MipLinear:
			return D3D12_FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR;
		case Portakal::SamplerFiltering::MinLinear_MagLinear_MipPoint:
			return D3D12_FILTER_MIN_MAG_LINEAR_MIP_POINT;
		case Portakal::SamplerFiltering::MinLinear_MagLinear_MipLinear:
			return D3D12_FILTER_MIN_MAG_MIP_LINEAR;
		case Portakal::SamplerFiltering::Anisotropic:
			return D3D12_FILTER_ANISOTROPIC;
		default:
			ASSERT(false, "DX12SamplerUtils", "Invalid SamplerFilter");
			break;
		}
	}
}