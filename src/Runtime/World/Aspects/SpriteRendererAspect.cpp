#include "SpriteRendererAspect.h"
#include <Runtime/World/Aspects/DisplayAspect.h>
#include <Runtime/Resource/RenderTarget/RenderTarget.h>
#include <Runtime/World/Scene.h>
#include <Runtime/Graphics/GraphicsDevice.h>
#include <Runtime/Graphics/GraphicsDeviceAPI.h>
#include <Runtime/Graphics/Command/CommandList.h>
#include <Runtime/World/Components/SpriteCamera.h>
#include <Runtime/World/Entity.h>

namespace Portakal
{
    void SpriteRendererAspect::RegisterCamera(SpriteCamera* pCamera)
    {
        mCameras.Add(pCamera);
    }
    void SpriteRendererAspect::RemoveCamera(SpriteCamera* pCamera)
    {
        mCameras.Remove(pCamera);
    }
    void SpriteRendererAspect::OnInitialize()
    {
        GraphicsDevice* pDefaultDevice = GraphicsDeviceAPI::GetDefaultDevice();
        if (pDefaultDevice == nullptr)
            return;

        mCmdList = pDefaultDevice->CreateGraphicsCommandList({});

        /*
        * Get all cameras
        */
        const Array<Entity*> entities = GetOwnerScene()->GetEntities();
        for (unsigned int entityIndex = 0; entityIndex < entities.GetCursor(); entityIndex++)
        {
            Entity* pEntity = entities[entityIndex];

            const Array<Component*> components = pEntity->GetComponents();
            for (unsigned int componentIndex = 0; componentIndex < components.GetCursor(); componentIndex++)
            {
                Component* pComponent = components[componentIndex];

                if (pComponent->GetType() == typeof(SpriteCamera))
                    RegisterCamera((SpriteCamera*)pComponent);
            }
        }
    }
    void SpriteRendererAspect::OnExecute()
    {
        DisplayAspect* pDisplayAspect = GetOwnerScene()->GetAspect<DisplayAspect>();
        if (pDisplayAspect == nullptr)
            return;

        RenderTarget* pDefaultDisplay = pDisplayAspect->GetDefaultDisplay();
        if (pDefaultDisplay == nullptr)
            return;

        /*
        * Render scene for each display 
        */
        mCmdList->Lock();
        for (unsigned int i = 0; i < mCameras.GetCursor(); i++)
        {
            const SpriteCamera* pCamera = mCameras[i];

            RenderTarget* pTarget = pCamera->GetRenderTarget();
            if (pTarget == nullptr)
            {
                pTarget = pDefaultDisplay;
            }

            mCmdList->BindFramebuffer(pTarget->GetFramebuffer());

            mCmdList->ClearColor(0,pCamera->GetClearColor());
            mCmdList->ClearColor(1, ColorRgbaF::DarkBlue());
        }
        mCmdList->Unlock();

        GraphicsDeviceAPI::GetDefaultDevice()->SubmitCommands(mCmdList);
        GraphicsDeviceAPI::GetDefaultDevice()->WaitForFinish();

    }
    void SpriteRendererAspect::OnFinalize()
    {
        mCameras.Clear();
    }
}