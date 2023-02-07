#pragma once
#include <Runtime/Core/Core.h>
#include <Editor/Project/Project.h>

namespace Portakal
{
	class PORTAKAL_API ProjectAPI
	{
		friend class ProjectModule;
	private:
		static ProjectAPI* sAPI;
	public:
		static Project GetProject();
	private:
		ProjectAPI(const Project& project);
		~ProjectAPI();
	private:
		Project mProject;
	};
}