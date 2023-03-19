#include "GraphicsModule.h"
#include <Runtime/Graphics/GraphicsDeviceAPI.h>
#include <Runtime/Graphics/GraphicsDevice.h>
#include <Runtime/Window/WindowAPI.h>

namespace Portakal
{
    void GraphicsModule::OnInitialize()
    {
        /*
        * Create devices
        */
        Array<GraphicsDevice*> windowedDevices;
        Array<GraphicsDevice*> standaloneDevices;

        for (unsigned int i = 0; i < _params.WindowedDescs.GetCursor(); i++)
        {
            WindowedGraphicsDeviceCreateDesc desc = _params.WindowedDescs[i];
            desc.pOwnerWindow = desc.pOwnerWindow == nullptr ? WindowAPI::GetDefaultWindow() : desc.pOwnerWindow;

            GraphicsDevice* pDevice = GraphicsDevice::CreateWindowed(desc);
            windowedDevices.Add(pDevice);
        }
        for (unsigned int i = 0; i < _params.StandaloneDescs.GetCursor(); i++)
        {
            GraphicsDevice* pDevice = GraphicsDevice::CreateStandalone(_params.StandaloneDescs[i]);
            standaloneDevices.Add(pDevice);
        }

    }
    void GraphicsModule::OnFinalize()
    {

    }
    void GraphicsModule::OnPreTick()
    {

    }
    void GraphicsModule::OnTick()
    {

    }
    void GraphicsModule::OnPostTick()
    {

    }
    void GraphicsModule::PreValidate()
    {

    }
    void GraphicsModule::PostValidate()
    {

    }
    void GraphicsModule::OnEvent(WindowEvent* pEvent)
    {
    }
}