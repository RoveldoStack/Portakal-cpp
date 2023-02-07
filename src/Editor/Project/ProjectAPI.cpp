#include "ProjectAPI.h"

namespace Portakal
{
	ProjectAPI* ProjectAPI::sAPI = nullptr;

	Project ProjectAPI::GetProject()
	{
		if (sAPI == nullptr)
			return {};

		return sAPI->mProject;
	}
	ProjectAPI::ProjectAPI(const Project& project)
	{
		sAPI = this;
		mProject = project;
	}
	ProjectAPI::~ProjectAPI()
	{
		sAPI = nullptr;
		mProject = {};
	}
}