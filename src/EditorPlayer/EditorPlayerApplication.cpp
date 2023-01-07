#include "EditorPlayerApplication.h"
#include <Runtime/Window/WindowAPI.h>
#include <exception>
#include <Runtime/Window/WindowEvent.h>
#include <Runtime/Message/MessageModule.h>
#include <Runtime/Log/Log.h>
#include <Runtime/Graphics/GraphicsDeviceAPI.h>
#include <Runtime/Graphics/CommandBuffer.h>

namespace Portakal
{
    void EditorPlayerApplication::RunCore()
    {
        CommandBuffer* pCmdBuffer = GraphicsDeviceAPI::GetDefaultDevice()->CreateCommandBuffer({});

        /*
        * Validate requirements
        */
        if (WindowAPI::GetDefaultWindow() == nullptr)
        {
            PostQuitMessage("No window api found!");
            return;
        }

        /*
        * Get modules
        */
        const Array<ApplicationModule*> tickableModules = GetTickableModules();
        const Array<ApplicationModule*> eventableModules = GetEventableModules();
        const Array<ApplicationModule*> validationModules = GetValidationModules();
        Window* pDefaultWindow = WindowAPI::GetDefaultWindow();

        /*
        * Initialize
        */
        pDefaultWindow->Show();

        while (!HasQuitRequest())
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
                for (int i = validationModules.GetCursor() - 1; i >= 0; i--)
                {
                    try
                    {
                        validationModules[i]->PreValidate();
                    }
                    catch(std::exception ex)
                    {
                        
                    }
                }

                /*
                * Post validate modules
                */
                for (unsigned int i = 0; i < validationModules.GetCursor(); i++)
                {
                    try
                    {
                        validationModules[i]->PostValidate();
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
            pDefaultWindow->PollEvents();

            /*
            * Validate window state
            */
            if(!pDefaultWindow->IsActive())
            {
                PostQuitMessage("Window is not active");
                continue;
            }

            /*
            * Broadcast events
            */
            const Array<WindowEvent*> events = pDefaultWindow->GetPolledEvents();
            for (unsigned int eventIndex = 0; eventIndex < events.GetCursor(); eventIndex++)
            {
                WindowEvent* pEvent = events[eventIndex];

                for (int i = eventableModules.GetCursor() - 1; i >= 0; i--)
                {
                    ApplicationModule* pModule = eventableModules[i];

                    pModule->OnEvent(pEvent);

                    if (pEvent->IsHandled())
                        break;
                }
            }

            /*
            * Tick modules
            */
            for (unsigned int i = 0; i < tickableModules.GetCursor(); i++)
            {
                tickableModules[i]->OnPreTick();
            }
            for (unsigned int i = 0; i < tickableModules.GetCursor(); i++)
            {
                tickableModules[i]->OnTick();
            }
            for (unsigned int i = 0; i < tickableModules.GetCursor(); i++)
            {
                tickableModules[i]->OnPostTick();
            }

            /*
            * Swapbuffers and device operations
            */
            pCmdBuffer->Lock();
            pCmdBuffer->BindFramebuffer(GraphicsDeviceAPI::GetDefaultDevice()->GetSwapchainFramebuffer());

            ViewportDesc viewport = {};
            viewport.Width = 1024;
            viewport.Height = 1024;
            viewport.X = 0;
            viewport.Y = 0;
            viewport.MinDepth = 0.0f;
            viewport.MaxDepth = 1.0f;
            pCmdBuffer->SetViewports({ {viewport} });

            pCmdBuffer->ClearColor(1, 0, 0, 1);
            pCmdBuffer->Unlock();

            GraphicsDeviceAPI::GetDefaultDevice()->SubmitCommands({ pCmdBuffer });
            GraphicsDeviceAPI::GetDefaultDevice()->Swapbuffers();
            GraphicsDeviceAPI::GetDefaultDevice()->WaitForFinish();

            /*
            * Set delta time
            */
        }
    }
}