#include "EditorPlayerApplication.h"
#include <Runtime/Window/WindowAPI.h>
#include <exception>
#include <Runtime/Window/WindowEvent.h>
#include <Runtime/Message/MessageModule.h>
#include <Runtime/Log/Log.h>
#include <Runtime/Graphics/GraphicsDeviceAPI.h>
#include <Runtime/Graphics/CommandList.h>
#include <Runtime/Platform/PlatformTime.h>
#include <Runtime/Time/Stopwatch.h>
#include <Runtime/Memory/SharedHeap.h>
#include <Runtime/Memory/OwnedHeap.h>
#include <Editor/Project/ProjectGenerator.h>

namespace Portakal
{
    void EditorPlayerApplication::Initialize()
    {
        _tickableModules = GetTickableModules();
        _eventableModules = GetEventableModules();
        _validationModules = GetValidationModules();

        _cmdBuffer = GraphicsDeviceAPI::GetDefaultDevice()->CreateGraphicsCommandList({});
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

        //ProjectGenerator::GenerateSync("TestProject", "C:/Users/Roveldo/Documents/Portakal");
    }
    void EditorPlayerApplication::PreTick()
    {
        
    }
    void EditorPlayerApplication::Tick()
    {


    }
    void EditorPlayerApplication::PostTick()
    {
        _defaultDevice->Swapbuffers();
        _defaultDevice->WaitForFinish();
    }
   
   
}