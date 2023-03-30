#include "DX11SamplerUtils.h"
#include <Runtime/Assert/Assert.h>

namespace Portakal
{
	D3D11_TEXTURE_ADDRESS_MODE DX11SamplerUtils::GetAddressMode(const SamplerAddress address)
	{
		switch (address)
		{
		case Portakal::SamplerAddress::Wrap:
			return D3D11_TEXTURE_ADDRESS_WRAP;
		case Portakal::SamplerAddress::Mirror:
			return D3D11_TEXTURE_ADDRESS_MIRROR;
		case Portakal::SamplerAddress::Clamp:
			return D3D11_TEXTURE_ADDRESS_CLAMP;
		case Portakal::SamplerAddress::Border:
			return D3D11_TEXTURE_ADDRESS_BORDER;
		default:
			ASSERT(false, "DX11SamplerUtils", "Invalid SamplerAddress!");
			break;
		}
	}
	D3D11_FILTER DX11SamplerUtils::GetFiltering(const SamplerFiltering filtering)
	{
		switch (filtering)
		{
		case Portakal::SamplerFiltering::MinPoint_MagPoint_MipPoint:
			return D3D11_FILTER_MIN_MAG_MIP_POINT;
		case Portakal::SamplerFiltering::MinPoint_MagPoint_MipLinear:
			return D3D11_FILTER_MIN_MAG_POINT_MIP_LINEAR;
		case Portakal::SamplerFiltering::MinPoint_MagLinear_MipPoint:
			return D3D11_FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT;
		case Portakal::SamplerFiltering::MinPoint_MagLinear_MipLinear:
			return D3D11_FILTER_MIN_POINT_MAG_MIP_LINEAR;
		case Portakal::SamplerFiltering::MinLinear_MagPoint_MipPoint:
			return D3D11_FILTER_MIN_LINEAR_MAG_MIP_POINT;
		case Portakal::SamplerFiltering::MinLinear_MagPoint_MipLinear:
			return D3D11_FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR;
		case Portakal::SamplerFiltering::MinLinear_MagLinear_MipPoint:
			return D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT;
		case Portakal::SamplerFiltering::MinLinear_MagLinear_MipLinear:
			return D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		case Portakal::SamplerFiltering::Anisotropic:
			return D3D11_FILTER_ANISOTROPIC;
		default:
			ASSERT(false, "DX11SamplerUtils", "Invalid SamplerFiltering!");
			break;
		}
	}
}