#include "GraphicsModule.h"
#include <Runtime/Graphics/GraphicsDeviceAPI.h>
#include <Runtime/Graphics/GraphicsDevice.h>
#include <Runtime/Window/WindowAPI.h>

namespace Portakal
{
    void GraphicsModule::OnInitialize()
    {
        /*
        * Create API
        */
        mAPI = new GraphicsDeviceAPI();

        /*
        * Create devices
        */
        Array<GraphicsDevice*> windowedDevices;
        Array<GraphicsDevice*> standaloneDevices;

        for (unsigned int i = 0; i < mParams.WindowedDescs.GetCursor(); i++)
        {
            WindowedGraphicsDeviceCreateDesc desc = mParams.WindowedDescs[i];
            desc.pOwnerWindow = desc.pOwnerWindow == nullptr ? WindowAPI::GetDefaultWindow() : desc.pOwnerWindow;

            GraphicsDevice* pDevice = GraphicsDevice::CreateWindowed(desc);
            windowedDevices.Add(pDevice);
        }
        for (unsigned int i = 0; i < mParams.StandaloneDescs.GetCursor(); i++)
        {
            GraphicsDevice* pDevice = GraphicsDevice::CreateStandalone(mParams.StandaloneDescs[i]);
            standaloneDevices.Add(pDevice);
        }
    }
    void GraphicsModule::OnFinalize()
    {
        delete mAPI;
        mAPI = nullptr;
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