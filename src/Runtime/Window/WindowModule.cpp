#include "WindowModule.h"
#include <Runtime/Window/WindowAPI.h>
#include <Runtime/Window/Window.h>
#include <Runtime/Application/Application.h>
#include <Runtime/Platform/PlatformMonitor.h>
#include <Runtime/Log/Log.h>
#
namespace Portakal
{
    void WindowModule::OnInitialize()
    {
        /*
        * Create API
        */
        mAPI = new WindowAPI();

        /*
        * Create windows
        */
        for (int i = 0; i < mParams.CreateDescs.GetCursor(); i++)
        {
            const WindowCreateDesc desc = mParams.CreateDescs[i];

            Window* pWindow = Window::Create(desc);

            GetOwnerApplication()->RegisterWindow(pWindow);

            mWindows.Add(pWindow);

            PlatformMonitor* pMonitor = PlatformMonitor::GetFromWindow(pWindow);
            LOG("WindowModule", "Width: %d, Height: %d", pMonitor->GetWidth(), pMonitor->GetHeight());
        }

    }
    void WindowModule::OnFinalize()
    {
        /*
        * Close windows
        */
        for (unsigned int i = 0; i < mWindows.GetCursor(); i++)
        {
            GetOwnerApplication()->RemoveWindow(mWindows[i]);
            delete mWindows[i];
        }
        mWindows.Clear();

        /*
        * Delete API
        */
        delete mAPI;
        mAPI = nullptr;
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