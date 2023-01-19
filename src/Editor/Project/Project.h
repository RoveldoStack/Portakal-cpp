#pragma once
#include <Runtime/Containers/String.h>
#include <Runtime/Containers/Guid.h>

namespace Portakal
{
	struct PORTAKAL_API Project
	{
		String Name;
		Guid ID;
		unsigned int VersionMajor;
		unsigned int VersionMinor;
		unsigned int VersionPatch;
		String ProjectFolderAbsolutePath;
	};
}