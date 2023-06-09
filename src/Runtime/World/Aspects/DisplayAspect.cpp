#include "DisplayAspect.h"
#include <Runtime/Resource/RenderTarget/RenderTargetResource.h>


namespace Portakal
{
    RenderTargetResource* DisplayAspect::GetDefaultDisplay() const noexcept
    {
        return mDisplays.GetCursor() > 0 ? mDisplays[0] : nullptr;
    }
    RenderTargetResource* DisplayAspect::GetDisplay(const unsigned int index) const noexcept
    {
        return mDisplays.GetCursor() > index ? mDisplays[index] : nullptr;
    }
    Array<RenderTargetResource*> DisplayAspect::GetDisplays() const noexcept
    {
        return mDisplays;
    }
    void DisplayAspect::SelectDisplay(const unsigned int index, RenderTargetResource* pRenderTarget)
    {
        /*
        * Validate if the index is valid
        */
        if (index >= mMaxDisplayCount)
        {
            LOG("DisplayAspect", "The given index[%d] is out of range, the max display count is %d!", index, mMaxDisplayCount);
            return;
        }
        
        /*
        * Set display
        */
        mDisplays[index] = pRenderTarget;
    }
    void DisplayAspect::RegisterDisplay(RenderTargetResource* pRenderTarget)
    {
        /*
        * Validate the given render target
        */
        if (pRenderTarget == nullptr || pRenderTarget->IsDestroyed())
            return;

        /*
        * Check range
        */
        for (unsigned int i = 0; i < mMaxDisplayCount; i++)
        {
            RenderTargetResource* pDisplayRenderTarget = mDisplays[i];
            if (pDisplayRenderTarget == nullptr || pDisplayRenderTarget->IsDestroyed())
            {
                mDisplays[i] = pRenderTarget;
                return;
            }
        }

        /*
        * Promt message
        */
        LOG("DisplayAspect", "Failed to put the requested render target to any display slot");
    }
    void DisplayAspect::RemoveDisplay(RenderTargetResource* pRenderTarget)
    {
        /*
        * Validate given render target
        */
        if (pRenderTarget == nullptr)
            return;

        /*
        * Try find
        */
        const int index = mDisplays.FindIndex(pRenderTarget);
        if (index == -1)
            return;
        mDisplays[index] = nullptr;
    }
    void DisplayAspect::Initialize()
    {
        mDisplays.Reserve(8,nullptr);
    }
    void DisplayAspect::Execute()
    {

    }
    void DisplayAspect::Finalize()
    {

    }
   
}