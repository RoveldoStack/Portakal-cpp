#include "DisplayAspect.h"

namespace Portakal
{
    RenderTarget* DisplayAspect::GetDefaultDisplay() const noexcept
    {
        return mDisplays.GetCursor() > 0 ? mDisplays[0] : nullptr;
    }
    RenderTarget* DisplayAspect::GetDisplay(const unsigned int index) const noexcept
    {
        return mDisplays.GetCursor() > index ? mDisplays[index] : nullptr;
    }
    Array<RenderTarget*> DisplayAspect::GetDisplays() const noexcept
    {
        return mDisplays;
    }
    void DisplayAspect::RegisterDisplay(RenderTarget* pTarget)
    {
        mDisplays.Add(pTarget);
    }
    void DisplayAspect::RemoveDisplay(RenderTarget* pTarget)
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