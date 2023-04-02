#include "ImGuiRendererModule.h"
#include <Runtime/Graphics/CommandList.h>
#include <Runtime/Graphics/GraphicsDevice.h>
#include <Runtime/Graphics/GraphicsDeviceAPI.h>
#include <Runtime/Assert/Assert.h>
#include <Editor/Renderer/ImGuiRenderer.h>
#include <Editor/Renderer/ImGuiAPI.h>
#include <Runtime/Resource/Texture/TextureResource.h>
#include <Runtime/Memory/SharedHeap.h>

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
        SharedHeap<TextureResource> texture(new TextureResource());

        GraphicsDevice* pDevice = GraphicsDeviceAPI::GetDefaultDevice();

        /*
        * Check for device
        */
        ASSERT(pDevice != nullptr, "ImGuiRendererModule", "There is no default graphics device");
        ASSERT(!pDevice->IsStandalone(), "ImGuiRendererModule", "The default graphics device is not a windowed device!");

        /*
        * Create command buffer
        */
        mCmdList = pDevice->CreateGraphicsCommandList({});

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

        //mCmdList->Lock();
        pRenderer->FinalizeRendering(mCmdList);
       // mCmdList->Unlock();

       // mDevice->SubmitCommands({ mCmdList });
       // mDevice->WaitForFinish();
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