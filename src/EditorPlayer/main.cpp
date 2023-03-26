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
#include <Runtime/Job/JobFiber.h>
namespace Portakal
{
	
	class TestJob : public Job
	{
	public:
		TestJob(const String& str,const unsigned int tickAmount) : mStr(str) , mTickAmount(tickAmount)
		{

		}
		virtual void Run() override
		{
			unsigned int count = 0;
			while (count!=5)
			{
				
				LOG("TestJob", "Output: %s",*mStr);
				PlatformThread::SleepCurrentThread(mTickAmount);
				count++;
			}
		}
	private:
		const String mStr;
		const unsigned int mTickAmount;
	};
	

	
}

Portakal::JobPool* pJobPool = nullptr;
int main(unsigned int argumentCount, const char** ppArguments)
{
	pJobPool = new Portakal::JobPool(12);

	Portakal::JobFiber* pFiber = new Portakal::JobFiber();
	pFiber->RegisterNode
	(
		{
		new Portakal::TestJob("First node first job",200),
		new Portakal::TestJob("First node second job",200)
		}
	);
	pFiber->RegisterNode
	(
		{
		new Portakal::TestJob("Second node first job",400),
		new Portakal::TestJob("Second node second job",400)
		}
	);

	pFiber->RegisterNode
	(
		{
		new Portakal::TestJob("Third node first job",100),
		new Portakal::TestJob("Third node second job",100)
		}
	);

	Portakal::JobFiber* pFiber2 = new Portakal::JobFiber();
	pFiber2->RegisterNode
	(
		{
		new Portakal::TestJob("Other node first job",350),
		new Portakal::TestJob("Other node second job",350)
		}
	);

	Portakal::JobFiber* pFiber3 = new Portakal::JobFiber();
	pFiber3->RegisterNode
	(
		{
		new Portakal::TestJob("Heavy node first job",350),
		new Portakal::TestJob("Heavy node second job",350),
		new Portakal::TestJob("Heavy node second job",350),
		new Portakal::TestJob("Heavy node second job",350),
		new Portakal::TestJob("Heavy node second job",350),
		new Portakal::TestJob("Heavy node second job",350)
		}
	);

	pJobPool->SubmitJobFiber(pFiber);
	pJobPool->SubmitJobFiber(pFiber2);
	pJobPool->SubmitJobFiber(pFiber3);
	

	pJobPool->SubmitJob<Portakal::TestJob>("Standalone job 0",350);
	pJobPool->SubmitJob<Portakal::TestJob>("Standalone job 1",350);
	pJobPool->SubmitJob<Portakal::TestJob>("Standalone job 2",350);
	pJobPool->SubmitJob<Portakal::TestJob>("Standalone job 3",350);
	pJobPool->SubmitJob<Portakal::TestJob>("Standalone job 4",350);
	pJobPool->SubmitJob<Portakal::TestJob>("Standalone job 5",350);
	pJobPool->SubmitJob<Portakal::TestJob>("Standalone job 6",350);


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
