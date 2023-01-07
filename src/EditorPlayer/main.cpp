#include <Runtime/Platform/PlatformMessage.h>
#include <Runtime/Window/Window.h>
#include "EditorPlayerApplication.h"
#include <Runtime/Message/MessageModule.h>
#include <Runtime/Window/WindowModule.h>
#include <Runtime/World/Entity.h>
#include <Runtime/World/Scene.h>
#include <Runtime/Yaml/Yaml.h>
#include <Runtime/Graphics/GraphicsModule.h>
#include <Runtime/Window/WindowAPI.h>

int main(unsigned int argumentCount, const char** ppArguments)
{
	/*
	* Initialize application
	*/
	Portakal::EditorPlayerApplication* pApplication = new Portakal::EditorPlayerApplication();

	/*
	* Create modules
	*/
	pApplication->CreateModule<Portakal::MessageModule>();

	Portakal::WindowModuleParams windowModuleParams = {};

	Portakal::WindowCreateDesc windowDesc = {};
	windowDesc.Name = "Portakal Editor Player";
	windowDesc.PositionX = 100;
	windowDesc.PositionY = 100;
	windowDesc.Width = 1024;
	windowDesc.Height = 1024;

	windowModuleParams.CreateDescs.Add(windowDesc);
	
	pApplication->CreateModule<Portakal::WindowModule>(windowModuleParams);

	Portakal::GraphicsModuleParams graphicsModuleParams = {};
	Portakal::WindowedGraphicsDeviceCreateDesc gdDesc = {};
	gdDesc.Backend = Portakal::GraphicsBackend::Directx12;
	gdDesc.BufferCount = 3;
	gdDesc.ColorFormat = Portakal::TextureFormat::R8_G8_B8_A8_UNorm;
	gdDesc.DepthStencilFormat = Portakal::TextureFormat::None;
	gdDesc.pOwnerWindow = nullptr;
	graphicsModuleParams.WindowedDescs.Add(gdDesc);

	pApplication->CreateModule<Portakal::GraphicsModule>(graphicsModuleParams);
	/*
	* Run
	*/
	pApplication->Run();

	/*
	* Finalize
	*/
	delete pApplication;

	return 0;
}

//Portakal::WindowCreateDesc windowDesc = {};
//windowDesc.Name = "Portakal Editor Player";
//windowDesc.PositionX = 100;
//windowDesc.PositionY = 100;
//windowDesc.Width = 1024;
//windowDesc.Height = 1024;
//
//Portakal::Window* pWindow = Portakal::Window::Create(windowDesc);
//
//pWindow->Show();
//
//while (1)
//{
//	pWindow->PollEvents();
//}