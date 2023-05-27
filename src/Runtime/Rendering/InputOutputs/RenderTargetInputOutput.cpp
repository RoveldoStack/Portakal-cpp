#include "RenderTargetInputOutput.h"

namespace Portakal
{
    RenderTargetInputOutput::RenderTargetInputOutput(const String& name, RenderPass* pOwnerPass) : RenderPassInputOutput(name,pOwnerPass),mRenderTarget(nullptr)
    {

    }
    void RenderTargetInputOutput::ForwardCore(void* pData)
    {
        mRenderTarget = (RenderTargetResource*)pData;
    }
    void* RenderTargetInputOutput::GetIOData() const noexcept
    {
        return mRenderTarget;
    }
}