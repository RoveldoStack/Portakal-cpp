#pragma once
#include <RUntime/DX11/Core.h>
#include <Runtime/Graphics/Sampler/Sampler.h>
#include <d3d11.h>

namespace Portakal
{
	class PORTAKAL_API DX11Sampler : public Sampler
	{
	public:
		DX11Sampler(const SamplerCreateDesc& desc, DX11Device* pDevice);
		virtual ~DX11Sampler() override;

		FORCEINLINE ID3D11SamplerState* GetDXSampler() const noexcept { return mSampler.Get(); }
	private:
		// Inherited via Sampler
		virtual void OnDestroy() override;
	private:
		DXPTR<ID3D11SamplerState> mSampler;
	};
}