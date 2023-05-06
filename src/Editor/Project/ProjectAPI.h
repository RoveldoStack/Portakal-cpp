#pragma once
#include <Runtime/Core/Core.h>
#include <Editor/Project/Project.h>
#include <Runtime/Object/API.h>

namespace Portakal
{
	/// <summary>
	/// API for enabling application to use the project related operation
	/// </summary>
	class PORTAKAL_API ProjectAPI : public API<ProjectAPI>
	{
		friend class ProjectModule;
	public:
		FORCEINLINE static Project* GetProject();
	private:
		ProjectAPI(const Project& project);
		virtual ~ProjectAPI() override;

		FORCEINLINE static void _SetProject(const Project& project);
	private:
		Project* mProject;
	};
}