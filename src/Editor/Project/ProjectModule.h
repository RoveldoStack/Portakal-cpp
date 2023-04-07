#pragma once
#include <Runtime/Application/ApplicationModule.h>

namespace Portakal
{
	/// <summary>
	/// Module params
	/// </summary>
	struct ProjectModuleCreateParams
	{
		String FolderPath;
		String Name;
	};

	class ProjectAPI;

	/// <summary>
	/// An application module which authors the core components of the project
	/// </summary>
	class PORTAKAL_API ProjectModule : public ApplicationModule
	{
		GENERATE_CLASS(ProjectModule);
	public:
		ProjectModule(const String& folderPath,const String& name) : mCreateParams({folderPath,name}) {}
		ProjectModule() = default;
		~ProjectModule() = default;

		GENERATE_APPLICATION_MODULE(false, false, false);
	private:

		// Inherited via ApplicationModule
		virtual void OnInitialize() override;
		virtual void OnFinalize() override;
		virtual void OnPreTick() override;
		virtual void OnTick() override;
		virtual void OnPostTick() override;
		virtual void PreValidate() override;
		virtual void PostValidate() override;
		virtual void OnEvent(WindowEvent* pEvent) override;
	private:
		const ProjectModuleCreateParams mCreateParams;
		ProjectAPI* mAPI;
	};

	//START_GENERATE_TYPE(ProjectModule);
	//START_TYPE_PROPERTIES(ProjectModule);
	//END_TYPE_PROPERTIES;
	//HAS_DEFAULT_CONSTRUCTOR(ProjectModule);
	//END_GENERATE_TYPE(ProjectModule);

#include "ProjectModule.reflect.h"
}