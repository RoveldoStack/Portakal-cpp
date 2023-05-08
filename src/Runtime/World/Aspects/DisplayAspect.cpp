#include "DisplayAspect.h"

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
    void DisplayAspect::RegisterDisplay(RenderTargetResource* pTarget)
    {
        mDisplays.Add(pTarget);
    }
    void DisplayAspect::RemoveDisplay(RenderTargetResource* pTarget)
    {
        mDisplays.Remove(pTarget);
    }
    void DisplayAspect::OnInitialize()
    {
    }
    void DisplayAspect::OnExecute()
    {
    }
    void DisplayAspect::OnFinalize()
    {
    }
}