#include "DomainModule.h"
#include <Runtime/Platform/PlatformDirectory.h>
#include <Editor/Domain/DomainAPI.h>
#include <Editor/Project/ProjectPaths.h>

namespace Portakal
{
	DomainModule::DomainModule()
	{

	}
	void DomainModule::OnInitialize()
	{
		const String domainFolderPath = ProjectPaths::GetProjectFolder() + "\\Domain";
		mAPI = new DomainAPI(domainFolderPath);
	}
	void DomainModule::OnFinalize()
	{
		delete mAPI;
	}
	void DomainModule::OnPreTick()
	{

	}
	void DomainModule::OnTick()
	{

	}
	void DomainModule::OnPostTick()
	{

	}
	void DomainModule::PreValidate()
	{

	}
	void DomainModule::PostValidate()
	{

	}
	void DomainModule::OnEvent(WindowEvent* pEvent)
	{

	}
}