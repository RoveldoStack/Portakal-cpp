#include "EditorPlayerApplication.h"
#include <Runtime/RuntimeModules.h>
#include <Runtime/Resource/ResourceSerializers.h>
#include <Editor/EditorModules.h>
#include <Editor/GUI/Component/EditorComponentVisualizerTemplates.h>
#include <Editor/GUI/MenuItem/MenuItemTemplates.h>
#include <Editor/GUI/Object/EditorObjectVisualizerTemplates.h>
#include <Editor/GUI/Window/GUIWindowTemplates.h>
#include <Editor/Asset/AsserSerializers.h>
#include <Editor/Asset/AssetAuthorizationTools.h>
#include <Editor/Asset/AssetImporters.h>
#include <Editor/Asset/AssetOpenOperations.h>
#include <Editor/Asset/AssetVisualizers.h>
#include <Runtime/Job/IJob.h>
#include <thread>
#include <Runtime/Win32/Win32Thread.h>

namespace Portakal
{
	
	class TestJob : public IJob
	{
	public:
		TestJob(const String& str) : mStr(str)
		{

		}
		virtual void Run() override
		{
			while (true)
			{
				LOG("TestJob", "Output: %s",*mStr);
				PlatformThread::WaitCurrentThread(100);
			}
		}
	private:
		const String mStr;
	};
	

	
}

int main(unsigned int argumentCount, const char** ppArguments)
{
	Portakal::PlatformThread::Create<Portakal::TestJob>(2,"my test job implementation");

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
