#include "SpriteCamera.h"
#include <Runtime/World/Entity.h>
#include <Runtime/World/Scene.h>
#include <Runtime/World/Aspects/SpriteRendererAspect.h>

namespace Portakal
{
    void SpriteCamera::SetRenderTarget(RenderTargetResource* pTarget)
    {
        mTarget = pTarget;
    }
    void SpriteCamera::DestroyCore()
    {

    }
    void SpriteCamera::OnInitialize()
    {
        mClearColor = ColorRgbaF::DarkGreen();

        SpriteRendererAspect* pAspect = GetOwnerEntity()->GetOwnerScene()->GetAspect<SpriteRendererAspect>();
        if (pAspect == nullptr)
            return;

        pAspect->RegisterCamera(this);
    }
    void SpriteCamera::OnFinalize()
    {

        SpriteRendererAspect* pAspect = GetOwnerEntity()->GetOwnerScene()->GetAspect<SpriteRendererAspect>();
        if (pAspect == nullptr)
            return;

        pAspect->RemoveCamera(this);
    }
}