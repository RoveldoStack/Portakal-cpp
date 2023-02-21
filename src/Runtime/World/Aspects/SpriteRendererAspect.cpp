#include "SpriteRendererAspect.h"
#include <Runtime/World/Aspects/DisplayAspect.h>
#include <Runtime/Resource/RenderTarget/RenderTarget.h>
#include <Runtime/World/Scene.h>
#include <Runtime/Graphics/GraphicsDevice.h>
#include <Runtime/Graphics/GraphicsDeviceAPI.h>
#include <Runtime/Graphics/CommandList.h>

namespace Portakal
{
    void SpriteRendererAspect::OnInitialize()
    {
        GraphicsDevice* pDefaultDevice = GraphicsDeviceAPI::GetDefaultDevice();
        if (pDefaultDevice == nullptr)
            return;

        mCmdList = pDefaultDevice->CreateGraphicsCommandList({});
    }
    void SpriteRendererAspect::OnExecute()
    {
        /*
        * Get display aspect
        */
        const DisplayAspect* pDisplayAspect = GetOwnerScene()->GetAspect<DisplayAspect>();
        if (pDisplayAspect == nullptr)
            return;

        /*
        * Get available displays
        */
        const Array<RenderTarget*> displays = pDisplayAspect->GetDisplays();
        if (displays.GetCursor() == 0)
            return;

        /*
        * Render scene for each display 
        */
        mCmdList->Lock();
        for (unsigned int i = 0; i < displays.GetCursor(); i++)
        {
            const RenderTarget* pRt = displays[i];

            mCmdList->BindFramebuffer(pRt->GetFramebuffer());

            mCmdList->ClearColor(0, 1, 0, 0, 1);
        }
        mCmdList->Unlock();

        GraphicsDeviceAPI::GetDefaultDevice()->SubmitCommands(mCmdList);
        GraphicsDeviceAPI::GetDefaultDevice()->WaitForFinish();

    }
    void SpriteRendererAspect::OnFinalize()
    {

    }
}