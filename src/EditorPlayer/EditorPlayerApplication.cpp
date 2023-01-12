#include "EditorPlayerApplication.h"
#include <Runtime/Window/WindowAPI.h>
#include <exception>
#include <Runtime/Window/WindowEvent.h>
#include <Runtime/Message/MessageModule.h>
#include <Runtime/Log/Log.h>
#include <Runtime/Graphics/GraphicsDeviceAPI.h>
#include <Runtime/Graphics/CommandBuffer.h>
#include <Runtime/Platform/PlatformTime.h>
#include <Runtime/Time/Stopwatch.h>
#include <Runtime/Memory/SharedHeap.h>
#include <Runtime/Memory/OwnedHeap.h>

namespace Portakal
{
    void EditorPlayerApplication::Initialize()
    {
        _tickableModules = GetTickableModules();
        _eventableModules = GetEventableModules();
        _validationModules = GetValidationModules();

        _cmdBuffer = GraphicsDeviceAPI::GetDefaultDevice()->CreateCommandBuffer({});
        _defaultWindow = WindowAPI::GetDefaultWindow();
        _defaultDevice = GraphicsDeviceAPI::GetDefaultDevice();

        /*
        * Validate requirements
        */
        if (WindowAPI::GetDefaultWindow() == nullptr)
        {
            PostQuitMessage("No window api found!");
            return;
        }

        /*
        * Show the window
        */
        _defaultWindow->Show();
    }
    bool EditorPlayerApplication::Tick()
    {
        /*
           * Check if has validation request
           */
        if (HasValidationRequest())
        {
            /*
            * Clear all reflection fields
            */

            /*
            * Pre validate modules
            */
            for (int i = _validationModules.GetCursor() - 1; i >= 0; i--)
            {
                try
                {
                    _validationModules[i]->PreValidate();
                }
                catch (std::exception ex)
                {

                }
            }

            /*
            * Post validate modules
            */
            for (unsigned int i = 0; i < _validationModules.GetCursor(); i++)
            {
                try
                {
                    _validationModules[i]->PostValidate();
                }
                catch (std::exception ex)
                {

                }
            }

            MarkValidated();
        }

        /*
        * Poll window events
        */
        _defaultWindow->PollEvents();

        /*
        * Validate window state
        */
        if (!_defaultWindow->IsActive())
        {
            PostQuitMessage("Window is not active");
            return false;
        }

        /*
        * Broadcast events
        */
        const Array<WindowEvent*> events = _defaultWindow->GetPolledEvents();
        for (unsigned int eventIndex = 0; eventIndex < events.GetCursor(); eventIndex++)
        {
            WindowEvent* pEvent = events[eventIndex];

            for (int i = _eventableModules.GetCursor() - 1; i >= 0; i--)
            {
                ApplicationModule* pModule = _eventableModules[i];

                pModule->OnEvent(pEvent);

                if (pEvent->IsHandled())
                    break;
            }
        }

        /*
        * Tick modules
        */
        for (unsigned int i = 0; i < _tickableModules.GetCursor(); i++)
        {
            _tickableModules[i]->OnPreTick();
        }
        for (unsigned int i = 0; i < _tickableModules.GetCursor(); i++)
        {
            _tickableModules[i]->OnTick();
        }
        for (unsigned int i = 0; i < _tickableModules.GetCursor(); i++)
        {
            _tickableModules[i]->OnPostTick();
        }

        /*
        * Swapbuffers and device operations
        */
        _defaultDevice->Swapbuffers();
        _defaultDevice->WaitForFinish();

        return true;
    }
   
}