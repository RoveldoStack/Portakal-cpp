#include "DX12Sampler.h"
#include <Runtime/DX12/DX12Device.h>

namespace Portakal
{
    DX12Sampler::DX12Sampler(const SamplerCreateDesc& desc, DX12Device* pDevice) : Sampler(desc)
    {

    }
    DX12Sampler::~DX12Sampler()
    {

    }
    void DX12Sampler::OnDestroy()
    {
    }
}