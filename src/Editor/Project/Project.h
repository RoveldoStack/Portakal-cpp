#pragma once
#include <Runtime/Containers/String.h>
#include <Runtime/Containers/Guid.h>
#include <Runtime/Reflection/Reflection.h>

namespace Portakal
{
	/// <summary>
	/// Represents a project header data
	/// </summary>
	PSTRUCT();
	struct PORTAKAL_API Project : public Class
	{
		GENERATE_CLASS(Project);

		/// <summary>
		/// Name of the project
		/// </summary>
		PFIELD();
		String Name;

		/// <summary>
		/// ID of the project
		/// </summary>
		PFIELD();
		Guid ID;

		/// <summary>
		/// Major version
		/// </summary>
		PFIELD();
		UInt VersionMajor;

		/// <summary>
		/// Minor version
		/// </summary>
		PFIELD();
		UInt VersionMinor;

		/// <summary>
		/// Patch version
		/// </summary>
		PFIELD();
		UInt VersionPatch;

		/// <summary>
		/// Project folder absolute path
		/// </summary>
		PFIELD();
		String ProjectFolderAbsolutePath;
	};

#include "Project.reflect.h"
}