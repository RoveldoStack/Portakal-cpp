#include "ProjectAPI.h"

namespace Portakal
{
	Project* ProjectAPI::GetProject()
	{
		ProjectAPI* pAPI = GetUnderlyingAPI();
		if (pAPI == nullptr)
			return nullptr;

		return pAPI->mProject;
	}
	

	ProjectAPI::ProjectAPI(const Project& project)
	{
		mProject = new Project();
		*mProject = project;
	}

	ProjectAPI::~ProjectAPI()
	{
		delete mProject;
		mProject = nullptr;
	}
}