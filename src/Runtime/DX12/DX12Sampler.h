#pragma once
#include <Runtime/Graphics/Sampler.h>
#include <Runtime/DX12/Core.h>
#include <d3d12.h>

namespace Portakal
{
	/// <summary>
	/// D3D12 implementation of a texture sampler
	/// </summary>
	class PORTAKAL_API DX12Sampler : public Sampler
	{
	public:
		DX12Sampler(const SamplerCreateDesc& desc, DX12Device* pDevice);
		virtual ~DX12Sampler() override;

	private:

		// Inherited via Sampler
		virtual void OnDestroy() override;
	};
}