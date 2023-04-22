#pragma once
#include <Runtime/Graphics/Sampler/SamplerCreateDesc.h>
#include <Runtime/Graphics/ComparisionMethod.h>
#include <d3d12.h>

namespace Portakal
{
	class PORTAKAL_API DX12SamplerUtils
	{
	public:
		DX12SamplerUtils() = delete;
		~DX12SamplerUtils() = delete;

		FORCEINLINE static D3D12_TEXTURE_ADDRESS_MODE GetWrapMode(const SamplerAddress address);
		FORCEINLINE static D3D12_STATIC_BORDER_COLOR GetBorderColor(const SamplerBorderColor color);
		FORCEINLINE static D3D12_FILTER GetFilter(const SamplerFiltering filter);
	};
}