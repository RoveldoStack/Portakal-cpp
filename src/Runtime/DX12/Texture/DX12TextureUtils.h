#pragma once
#include <Runtime/Graphics/Texture/TextureCreateDesc.h>
#include <d3d12.h>

namespace Portakal
{
	/// <summary>
	/// Util class for D3D12 texture conversions
	/// </summary>
	class PORTAKAL_API DX12TextureUtils
	{
	public:
		DX12TextureUtils() = delete;
		~DX12TextureUtils() = delete;

		FORCEINLINE static D3D12_RESOURCE_DIMENSION GetTextureDimension(const TextureType type);
		FORCEINLINE static D3D12_RESOURCE_FLAGS GetTextureResourceFlags(const TextureUsage usage);
	};
}