#pragma once
#include <Editor/Project/Project.h>
#include <Runtime/Reflection/Type.h>

namespace Portakal
{
	struct PORTAKAL_API ProjectYaml : public Class
	{
		GENERATE_CLASS(ProjectYaml);

		String Name;
		Guid ID;
		unsigned int VersionMajor;
		unsigned int VersionMinor;
		unsigned int VersionPatch;
	};

	START_GENERATE_TYPE(ProjectYaml);
	START_TYPE_PROPERTIES(ProjectYaml);
	END_TYPE_PROPERTIES;
	HAS_DEFAULT_CONSTRUCTOR(ProjectYaml);
	END_GENERATE_TYPE(ProjectYaml);
}