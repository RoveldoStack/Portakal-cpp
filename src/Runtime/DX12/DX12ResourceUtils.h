#pragma once
#include <Runtime/Graphics/GraphicsResourceType.h>
#include <Runtime/Graphics/TextureCreateDesc.h>
#include <d3d12.h>

namespace Portakal
{
	class PORTAKAL_API DX12ResourceUtils
	{
	public:
		DX12ResourceUtils() = delete;
		~DX12ResourceUtils() = delete;

		FORCEINLINE static D3D12_SRV_DIMENSION GetTextureSRVDimension(const TextureType type);
	};
}