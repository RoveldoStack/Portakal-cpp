#pragma once
#include <Runtime/Graphics/Sampler/SamplerAddress.h>
#include <Runtime/Graphics/Sampler/SamplerBorderColor.h>
#include <Runtime/Graphics/Sampler/SamplerFiltering.h>
#include <d3d11.h>

namespace Portakal
{
	class PORTAKAL_API DX11SamplerUtils
	{
	public:
		DX11SamplerUtils() = delete;
		~DX11SamplerUtils() = delete;

		FORCEINLINE static D3D11_TEXTURE_ADDRESS_MODE GetAddressMode(const SamplerAddress address);
		FORCEINLINE static D3D11_FILTER GetFiltering(const SamplerFiltering filtering);
	};
}