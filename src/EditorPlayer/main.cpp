#include <Runtime/Platform/PlatformMessage.h>
#include <Runtime/Yaml/Yaml.h>
#include <Runtime/Window/Window.h>
#include "EditorPlayerApplication.h"
#include <Runtime/Message/MessageModule.h>
#include <Runtime/Window/WindowModule.h>
#include <Runtime/World/Entity.h>
#include <Runtime/World/Scene.h>
#include <Runtime/Graphics/GraphicsModule.h>
#include <Runtime/Window/WindowAPI.h>
#include <Editor/Renderer/ImGuiExecutorModule.h>
#include <Editor/Renderer/ImGuiRendererModule.h>
#include <Editor/GUI/Window/GUIWindowModule.h>
#include <Editor/GUI/MenuItem/MenuItemTemplates.h>
#include <Editor/GUI/MenuItem/GUIMainMenuItemModule.h>
#include <Editor/Project/ProjectModule.h>
#include <Editor/GUI/Window/Templates/DomainObserverWindow.h>
#include <Editor/GUI/Window/Templates/WorldObserverWindow.h>
#include <Editor/GUI/Window/Templates/ObjectObserverWindow.h>
#include <Editor/GUI/Window/Templates/GameObserverWindow.h>
#include <Editor/Domain/DomainModule.h>
#include <Editor/Resource/EditorResourceModule.h>
#include <Runtime/Platform/PlatformMonitor.h>
#include <Runtime/World/SceneModule.h>
#include <Runtime/Resource/ResourceModule.h>
#include <Runtime/Resource/Texture/TextureSerializer.h>


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
	windowDesc.PositionX = 0;
	windowDesc.PositionY = 0;
	windowDesc.Width = 2560;
	windowDesc.Height = 1440;

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
	pApplication->CreateModule<Portakal::ResourceModule>();
	pApplication->CreateModule<Portakal::SceneModule>();

	/*
	* Create project module
	*/
	const Portakal::String projectFolderPath = "C:\\Users\\Roveldo\\Documents\\Portakal\\TestProject";
	const Portakal::String projectName = "TestProject";
	pApplication->CreateModule<Portakal::ProjectModule>(projectFolderPath, projectName);

	
	/*
	* Create domain module
	*/
	pApplication->CreateModule<Portakal::DomainModule>();


	pApplication->CreateModule<Portakal::ImGuiExecutorModule>();

	/*
	* Create editor resource module
	*/
	Portakal::Array<Portakal::EditorResourceRequest> resourceRequests;
	resourceRequests.Add({ "FolderIcon.png",Portakal::EditorResourceType::Image });
	resourceRequests.Add({ "testIcon.png",Portakal::EditorResourceType::Image });
	resourceRequests.Add({ "ComponentIcon.png",Portakal::EditorResourceType::Image });
	resourceRequests.Add({ "DefaultIcon.png",Portakal::EditorResourceType::Image });
	resourceRequests.Add({ "InvalidIcon.png",Portakal::EditorResourceType::Image });
	resourceRequests.Add({ "SceneAspectIcon.png",Portakal::EditorResourceType::Image });
	resourceRequests.Add({ "SceneEntityIcon.png",Portakal::EditorResourceType::Image });
	resourceRequests.Add({ "SceneIcon.png",Portakal::EditorResourceType::Image });
	resourceRequests.Add({ "ShaderIcon.png",Portakal::EditorResourceType::Image });
	resourceRequests.Add({ "TextIcon.png",Portakal::EditorResourceType::Image });

	pApplication->CreateModule<Portakal::EditorResourceModule>(resourceRequests);

	pApplication->CreateModule<Portakal::GUIWindowModule>();
	pApplication->CreateModule<Portakal::GUIMainMenuItemModule>();

	pApplication->CreateModule<Portakal::ImGuiRendererModule>();

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
