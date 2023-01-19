#include "ImGuiExecutorModule.h"
#include <Runtime/Graphics/GraphicsDeviceAPI.h>
#include <Runtime/Graphics/GraphicsDevice.h>
#include <Runtime/Assert/Assert.h>
#include <Runtime/Time/Time.h>
#include <Editor/Renderer/ImGuiAPI.h>

namespace Portakal
{
    ImGuiExecutorModule::ImGuiExecutorModule()
    {

    }
    ImGuiExecutorModule::~ImGuiExecutorModule()
    {

    }
    void ImGuiExecutorModule::OnInitialize()
    {
        GraphicsDevice* pDefaultDevice = GraphicsDeviceAPI::GetDefaultDevice();

        /*
        * Validate device
        */
        ASSERT(pDefaultDevice != nullptr, "ImGuiExecutorFragment", "There is no default graphics device");
        ASSERT(!pDefaultDevice->IsStandalone(), "ImGuiExecutorFragment", "The default graphics device is not a windowed device!");

        _renderer = ImGuiRenderer::Create(pDefaultDevice);
        _api = new ImGuiAPI(_renderer);
    }
    void ImGuiExecutorModule::OnFinalize()
    {
        delete _renderer;
    }
    void ImGuiExecutorModule::OnPreTick()
    {

    }
    void ImGuiExecutorModule::OnTick()
    {
        _renderer->StartRendering(Time::GetDeltaTime());
    }
    void ImGuiExecutorModule::OnPostTick()
    {

    }
    void ImGuiExecutorModule::PreValidate()
    {

    }
    void ImGuiExecutorModule::PostValidate()
    {

    }
    void ImGuiExecutorModule::OnEvent(WindowEvent* pEvent)
    {
        _renderer->OnEvent(pEvent);
    }
}