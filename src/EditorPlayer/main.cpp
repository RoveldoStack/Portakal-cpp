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
#include <Runtime/Job/Job.h>
#include <Runtime/Job/JobPool.h>

namespace Portakal
{
	
	class TestJob : public Job
	{
	public:
		TestJob(const String& str) : mStr(str)
		{

		}
		virtual void Run() override
		{
			unsigned int count = 0;
			while (true)
			{
				if (count == 5)
					return;

				LOG("TestJob", "Output: %s",*mStr);
				PlatformThread::SleepCurrentThread(700);
				count++;
			}
		}
	private:
		const String mStr;
	};
	

	
}

Portakal::JobPool* pJobPool = nullptr;
int main(unsigned int argumentCount, const char** ppArguments)
{
	pJobPool = new Portakal::JobPool(2);

	pJobPool->Submit<Portakal::TestJob>("Job 0");
	pJobPool->Submit<Portakal::TestJob>("Job 1");
	pJobPool->Submit<Portakal::TestJob>("Job 2");
	pJobPool->Submit<Portakal::TestJob>("Job 3");
	pJobPool->Submit<Portakal::TestJob>("Job 4");
	pJobPool->Submit<Portakal::TestJob>("Job 5");
	pJobPool->Submit<Portakal::TestJob>("Job 6");


	//Portakal::PlatformThread::Create<Portakal::TestJob>(2,"Job 0");

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
