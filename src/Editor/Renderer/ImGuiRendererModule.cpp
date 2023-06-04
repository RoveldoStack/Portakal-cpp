#include "ImGuiRendererModule.h"
#include <Runtime/Graphics/Command/CommandList.h>
#include <Runtime/Graphics/GraphicsDevice.h>
#include <Runtime/Graphics/GraphicsDeviceAPI.h>
#include <Runtime/Assert/Assert.h>
#include <Editor/Renderer/ImGuiRenderer.h>
#include <Editor/Renderer/ImGuiAPI.h>
#include <Runtime/Resource/Texture/TextureResource.h>
#include <Runtime/Memory/SharedSafeHeap.h>
#include <Runtime/Graphics/Swapchain/Swapchain.h>

namespace Portakal
{
    ImGuiRendererModule::ImGuiRendererModule() : mCmdList(nullptr),mDevice(nullptr)
    {

    }
    ImGuiRendererModule::~ImGuiRendererModule()
    {

    }
    void ImGuiRendererModule::OnInitialize()
    {
        SharedSafeHeap<TextureResource> texture(new TextureResource());

        GraphicsDevice* pDevice = GraphicsDeviceAPI::GetDefaultDevice();

        /*
        * Check for device
        */
        ASSERT(pDevice != nullptr, "ImGuiRendererModule", "There is no default graphics device");
        ASSERT(!pDevice->IsStandalone(), "ImGuiRendererModule", "The default graphics device is not a windowed device!");

        /*
        * Create command buffer
        */
        mCmdList = pDevice->CreateCommandList({});

        mDevice = pDevice;
    }
    void ImGuiRendererModule::OnFinalize()
    {

    }
    void ImGuiRendererModule::OnPreTick()
    {

    }
    void ImGuiRendererModule::OnTick()
    {
        ImGuiRenderer* pRenderer = ImGuiAPI::GetDefaultRenderer();

        if(pRenderer != nullptr)
            pRenderer->FinalizeRendering(mDevice->GetSwapchain()->GetFramebuffer());
    }
    void ImGuiRendererModule::OnPostTick()
    {

    }
    void ImGuiRendererModule::PreValidate()
    {

    }
    void ImGuiRendererModule::PostValidate()
    {

    }
    void ImGuiRendererModule::OnEvent(WindowEvent* pEvent)
    {

    }
}