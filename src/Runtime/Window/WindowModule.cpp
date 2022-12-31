#include "WindowModule.h"
#include <Runtime/Window/WindowAPI.h>

namespace Portakal
{
    void WindowModule::OnInitialize()
    {
        _api = new WindowAPI(_params.CreateDescs);
    }
    void WindowModule::OnFinalize()
    {
        delete _api;
        _api = nullptr;
    }
    void WindowModule::OnPreTick()
    {
    }
    void WindowModule::OnTick()
    {
    }
    void WindowModule::OnPostTick()
    {
    }
    void WindowModule::PreValidate()
    {
    }
    void WindowModule::PostValidate()
    {
    }
    void WindowModule::OnEvent(WindowEvent* pEvent)
    {
    }
}