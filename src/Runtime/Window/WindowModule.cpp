#include "WindowModule.h"
#include <Runtime/Window/WindowAPI.h>
#include <Runtime/Window/Window.h>
#include <Runtime/Application/Application.h>

namespace Portakal
{
    void WindowModule::OnInitialize()
    {
        for (int i = 0; i < mParams.CreateDescs.GetCursor(); i++)
        {
            const WindowCreateDesc desc = mParams.CreateDescs[i];

            Window* pWindow = Window::Create(desc);

            GetOwnerApplication()->RegisterWindow(pWindow);

            mWindows.Add(pWindow);
        }

        mAPI = new WindowAPI(mWindows);
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