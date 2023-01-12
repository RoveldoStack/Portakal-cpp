#include "ImGuiRendererModule.h"
#include <Runtime/Graphics/CommandBuffer.h>
#include <Runtime/Graphics/GraphicsDevice.h>
#include <Runtime/Graphics/GraphicsDeviceAPI.h>
#include <Runtime/Assert/Assert.h>
#include <Editor/Renderer/ImGuiRenderer.h>
#include <Editor/Renderer/ImGuiAPI.h>

namespace Portakal
{
    ImGuiRendererModule::ImGuiRendererModule() : _cmdBuffer(nullptr),_device(nullptr)
    {

    }
    ImGuiRendererModule::~ImGuiRendererModule()
    {

    }
    void ImGuiRendererModule::OnInitialize()
    {
        GraphicsDevice* pDevice = GraphicsDeviceAPI::GetDefaultDevice();

        /*
        * Check for device
        */
        ASSERT(pDevice != nullptr, "ImGuiRendererModule", "There is no default graphics device");
        ASSERT(!pDevice->IsStandalone(), "ImGuiRendererModule", "The default graphics device is not a windowed device!");

        /*
        * Create command buffer
        */
        _cmdBuffer = pDevice->CreateCommandBuffer({});

        _device = pDevice;
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

        _cmdBuffer->Lock();
        pRenderer->FinalizeRendering(_cmdBuffer);
        _cmdBuffer->Unlock();

        _device->SubmitCommands({ _cmdBuffer });
        _device->WaitForFinish();
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