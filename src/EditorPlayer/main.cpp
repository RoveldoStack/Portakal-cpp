#include "EditorPlayerApplication.h"
#include <Runtime/RuntimeModules.h>
#include <Runtime/Resource/ResourceSerializers.h>
#include <Editor/EditorModules.h>
#include <Editor/GUI/Component/EditorComponentVisualizerTemplates.h>
#include <Editor/GUI/MenuItem/MenuItemTemplates.h>
#include <Editor/GUI/Object/EditorObjectVisualizerTemplates.h>
#include <Editor/GUI/Window/GUIWindowTemplates.h>
#include <Editor/Asset/AsserSerializers.h>
#include <Editor/Asset/AssetAuthoringTools.h>
#include <Editor/Asset/AssetImporters.h>
#include <Editor/Asset/AssetOpenOperations.h>
#include <Editor/Asset/AssetVisualizers.h>
#include <Runtime/Job/Job.h>
#include <Runtime/Platform/PlatformInfo.h>
#include <Runtime/Job/JobSystem.h>
#include <Runtime/Memory/SharedSafeHeap.h>
#include <Runtime/Math/Matrix4x4.h>
#include <Runtime/Platform/PlatformTime.h>
#include <Editor/Asset/YamlSerializers.h>
#include <Runtime/World/Components/TestComponent.h>
#include <iostream>
#include <Runtime/Yaml/YamlDefaultSerializer.h>
#include <Runtime/Graphics/Pipeline/Rasterizer/FrontFaceDirection.h>
#include <Runtime/Graphics/Pipeline/Rasterizer/FaceCullMode.h>
#include <Runtime/Object/GarbageCollector.h>
#include <Editor/GUI/Object/EditorObjectModule.h>

namespace Portakal
{
	void Test()
	{
		
	}
}

int main(unsigned int argumentCount, const char** ppArguments)
{
	Portakal::GarbageCollector::Initialize();
	Portakal::JobSystem::Initialize();

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
	gdDesc.Backend = Portakal::GraphicsBackend::Directx11;
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
	pApplication->CreateModule<Portakal::EditorObjectModule>();

	pApplication->CreateModule<Portakal::GUIWindowModule>();
	//pApplication->CreateModule<Portakal::GUIMainMenuItemModule>();

	pApplication->CreateModule<Portakal::ImGuiRendererModule>();
	pApplication->CreateModule<Portakal::InputModule>();

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
