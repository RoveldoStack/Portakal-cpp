#pragma once
#include <Runtime/Graphics/TextureUsage.h>
#include <d3d11.h>

namespace Portakal
{
	class PORTAKAL_API DX11TextureUtils
	{
	public:
		DX11TextureUtils() = delete;
		~DX11TextureUtils() = delete;

		FORCEINLINE static UINT GetTextureUsageFlags(const TextureUsage usage);
		FORCEINLINE static UINT GetCpuFlags(const TextureUsage usage);
		FORCEINLINE static D3D11_USAGE GetUsage(const TextureUsage usage);
	};
}