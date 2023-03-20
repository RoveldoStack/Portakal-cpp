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
	public:
		FORCEINLINE static Project GetProject() { return sProject; }
	private:
		static Project sProject;
	private:
		ProjectAPI() = delete;
		~ProjectAPI() = delete;
	};
}