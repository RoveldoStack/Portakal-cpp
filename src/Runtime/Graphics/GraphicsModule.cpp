#include "GraphicsModule.h"
#include <Runtime/Graphics/GraphicsDeviceAPI.h>

namespace Portakal
{
    void GraphicsModule::OnInitialize()
    {
        /*
        * Create devices
        */
        Array<GraphicsDevice*> windowedDevices;
        Array<GraphicsDevice*> standaloneDevices;

        _api = new GraphicsDeviceAPI(windowedDevices,standaloneDevices);
    }
    void GraphicsModule::OnFinalize()
    {
        delete _api;
        _api = nullptr;
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