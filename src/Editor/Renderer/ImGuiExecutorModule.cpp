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

        /*
        * Create renderer
        */
        mRenderer = new ImGuiRenderer(pDefaultDevice);

        /*
        * Create api
        */
        mAPI = new ImGuiAPI(mRenderer);
    }
    void ImGuiExecutorModule::OnFinalize()
    {
        delete mAPI;
        mAPI = nullptr;
        delete mRenderer;
        mRenderer = nullptr;
    }
    void ImGuiExecutorModule::OnPreTick()
    {

    }
    void ImGuiExecutorModule::OnTick()
    {
        mRenderer->StartRendering(Time::GetDeltaTime());
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
        mRenderer->OnEvent(pEvent);
    }
}