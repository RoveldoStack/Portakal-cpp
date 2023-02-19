#pragma once
#include <Runtime/Core/Core.h>
#include <Editor/Project/Project.h>

namespace Portakal
{
	/// <summary>
	/// API for enabling application to use the project related operation
	/// </summary>
	class PORTAKAL_API ProjectAPI
	{
		friend class ProjectModule;
	private:
		static ProjectAPI* sAPI;
	public:
		/// <summary>
		/// Returns the current project header data
		/// </summary>
		/// <returns></returns>
		static Project GetProject();

	private:
		ProjectAPI(const Project& project);
		~ProjectAPI();
	private:
		Project mProject;
	};
}