#include "DX12ResourceUtils.h"
#include <Runtime/Assert/Assert.h>

namespace Portakal
{
	D3D12_SRV_DIMENSION DX12ResourceUtils::GetTextureSRVDimension( TextureType type)
	{
		switch (type)
		{
			case Portakal::TextureType::Texture1D:
				return D3D12_SRV_DIMENSION_TEXTURE1D;
			case Portakal::TextureType::Texture2D:
				return D3D12_SRV_DIMENSION_TEXTURE2D;
			case Portakal::TextureType::Texture3D:
				return D3D12_SRV_DIMENSION_TEXTURE3D;
			default:
				ASSERT(false, "DX12ResourceUtils", "Invalid TextureType!");
				break;
		}
	}
}