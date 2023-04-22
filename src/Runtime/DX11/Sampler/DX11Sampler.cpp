#include "DX11Sampler.h"
#include <Runtime/DX11/DX11Device.h>
#include <Runtime/Assert/Assert.h>
#include <Runtime/DX11/Sampler/DX11SamplerUtils.h>
#include <Runtime/DX11/Pipeline/DX11PipelineUtils.h>
namespace Portakal
{
	DX11Sampler::DX11Sampler(const SamplerCreateDesc& desc, DX11Device* pDevice) : Sampler(desc)
	{
		float pColor[4];

		D3D11_SAMPLER_DESC samplerDesc = {};
		samplerDesc.AddressU = DX11SamplerUtils::GetAddressMode(desc.AddressU);
		samplerDesc.AddressV = DX11SamplerUtils::GetAddressMode(desc.AddressV);
		samplerDesc.AddressW = DX11SamplerUtils::GetAddressMode(desc.AddressW);
		samplerDesc.BorderColor[0] = 0; // TODO: later
		samplerDesc.BorderColor[1] = 0;
		samplerDesc.BorderColor[2] = 0;
		samplerDesc.BorderColor[3] = 0;
		samplerDesc.ComparisonFunc = DX11PipelineUtils::GetComparision(desc.Comparision);
		samplerDesc.Filter = DX11SamplerUtils::GetFiltering(desc.Filtering);
		samplerDesc.MaxAnisotropy = desc.MaxAnisotropy;
		samplerDesc.MaxLOD = desc.MaxLod;
		samplerDesc.MinLOD = desc.MinLod;
		samplerDesc.MipLODBias = desc.LodBias;

		ASSERT(SUCCEEDED(pDevice->GetDXDevice()->CreateSamplerState(&samplerDesc, mSampler.GetAddressOf())),"DX11Sampler","Failed to create sampler");
	}
	DX11Sampler::~DX11Sampler()
	{
		mSampler.Reset();
	}
	void DX11Sampler::OnDestroy()
	{
		mSampler.Reset();
	}
}