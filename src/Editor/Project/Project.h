#pragma once
#include <Runtime/Containers/String.h>
#include <Runtime/Containers/Guid.h>
#include <Runtime/Reflection/Reflection.h>

namespace Portakal
{
	/// <summary>
	/// Represents a project header data
	/// </summary>
	struct PORTAKAL_API Project : public Class
	{
		GENERATE_CLASS(Project);

		/// <summary>
		/// Name of the project
		/// </summary>
		FIELD();
		String Name;

		/// <summary>
		/// ID of the project
		/// </summary>
		FIELD();
		Guid ID;

		/// <summary>
		/// Major version
		/// </summary>
		FIELD();
		UInt VersionMajor;

		/// <summary>
		/// Minor version
		/// </summary>
		FIELD();
		UInt VersionMinor;

		/// <summary>
		/// Patch version
		/// </summary>
		FIELD();
		UInt VersionPatch;

		/// <summary>
		/// Project folder absolute path
		/// </summary>
		FIELD();
		String ProjectFolderAbsolutePath;
	};

#include "Project.reflect.h"
}